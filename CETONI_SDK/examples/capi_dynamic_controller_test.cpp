//============================================================================
/// \file   capi_dynamic_controller_test.cpp
/// \author Uwe Kindler
/// \date   04.04.2016
/// \brief  Implementation of
//============================================================================


//============================================================================
//                                   INCLUDES
//============================================================================
#include <labbcan/c_api/labbCAN_Bus_API.h>
#include <labbcan/c_api/labbCAN_Controller_API.h>
#include <labbcan/c_api/labbCAN_AnalogIO_API.h>
#include <labbcan/c_api/labbCAN_DigIO_API.h>
#include <labbcan/common/labbcan_test_helpers.h>

#include <thread>
#include <usl/core/PollingTimer.h>
#include <diag/diag.h>
#include <iostream>


//using namespace Lcl;
using namespace std::chrono_literals;
using namespace Usl;
#define BOOST_TEST_MODULE capi_dynamic_controller_test
#include <boost/test/unit_test.hpp>

using namespace boost::unit_test;

/**
* Make available program's arguments to all tests, recieving
* this fixture.
*/
struct ArgsFixture {
   ArgsFixture(): argc(framework::master_test_suite().argc),
           argv(framework::master_test_suite().argv){}
   int argc;
   char **argv;
};

BOOST_GLOBAL_FIXTURE( ArgsFixture );
static long Result;

static dev_hdl ControlChannel;


//============================================================================
// Initialize C-API - open bus library
//============================================================================
BOOST_FIXTURE_TEST_CASE(testCapiOpen, ArgsFixture)
{
    using namespace boost::unit_test;
    const char* ConfigPath = "config/testconfig_qmixsdk";
    if (argc > 1)
    {
    	ConfigPath = argv[1];
    }

    Result = LCB_Open(ConfigPath, 0);
    REQUIRE_ERR_NOERR(Result);
}


//============================================================================
// Build dynamic controller channel
//============================================================================
BOOST_AUTO_TEST_CASE(testCapiBuildController)
{
	dev_hdl ControlLoopIn;
	dev_hdl ControlLoopOut;

	Result = LCAIO_LookupInChanByName("QmixQplus_1_AI0_PT100", &ControlLoopIn);
	REQUIRE_ERR_NOERR(Result);

	Result = LCAIO_LookupOutChanByName("QmixQplus_1_AO0_PWM", &ControlLoopOut);
	REQUIRE_ERR_NOERR(Result);

	Result = LCC_CreatePIDControlChannel(ControlLoopIn, ControlLoopOut, ANALOG, &ControlChannel);
	REQUIRE_ERR_NOERR(Result);
}


//============================================================================
// Build set control channel parameters
//============================================================================
BOOST_AUTO_TEST_CASE(testSetControlParam)
{
	Result = LCC_SetPIDParameter(ControlChannel, PID_PARAM_K, 3);
	REQUIRE_ERR_NOERR(Result);
	Result = LCC_SetPIDParameter(ControlChannel, PID_PARAM_T_D, 0);
	REQUIRE_ERR_NOERR(Result);
	Result = LCC_SetPIDParameter(ControlChannel, PID_PARAM_T_I, 260);
	REQUIRE_ERR_NOERR(Result);
	Result = LCC_SetPIDParameter(ControlChannel, PID_PARAM_DERIVATIVE_GAIN_LIMIT, 20);
	REQUIRE_ERR_NOERR(Result);
	Result = LCC_SetPIDParameter(ControlChannel, PID_PARAM_T_T, 250);
	REQUIRE_ERR_NOERR(Result);
	Result = LCC_SetPIDParameter(ControlChannel, PID_PARAM_MIN_U, 0);
	REQUIRE_ERR_NOERR(Result);
	Result = LCC_SetPIDParameter(ControlChannel, PID_PARAM_MAX_U, 100);
	REQUIRE_ERR_NOERR(Result);
	Result = LCC_SetPIDParameter(ControlChannel, PID_PARAM_DISABLED_U, 0);
	REQUIRE_ERR_NOERR(Result);
	Result = LCC_SetPIDParameter(ControlChannel, PID_PARAM_INITIAL_SETPOINT, 0);
	REQUIRE_ERR_NOERR(Result);
	Result = LCC_SetPIDParameter(ControlChannel, PID_PARAM_SAMPLE_TIME, 500);
	REQUIRE_ERR_NOERR(Result);
}


//============================================================================
// Checks if start of bus and logging works properly
//============================================================================
BOOST_AUTO_TEST_CASE(testBusStart)
{
	Result = LCB_Start();
    BOOST_CHECK_EQUAL(Result, ERR_NOERR);
    Result = LCB_Log("C-API Log Test Message");
    BOOST_CHECK_EQUAL(Result, ERR_NOERR);
}


//============================================================================
// Checks if start of bus and logging works properly
//============================================================================
BOOST_AUTO_TEST_CASE(testControlLoop)
{
	double Setpoint = 50;

	// The Q+ module has a special digital enable output that we need to set
	// to enable the PWM output
	dev_hdl DigOutHeatingEnable; ///< this is a special output for enabling heating
	Result = LCDIO_LookupOutChanByName("QmixQplus_1_DO0_INA", &DigOutHeatingEnable);
	REQUIRE_ERR_NOERR(Result);
	Result = LCDIO_WriteOn(DigOutHeatingEnable, 1);
	REQUIRE_ERR_NOERR(Result);

	// Now we write the setpoint and enable the control loop
	Result = LCC_WriteSetPoint(ControlChannel, Setpoint);
	REQUIRE_ERR_NOERR(Result);
	Result = LCC_EnableControlLoop(ControlChannel, 1);
	REQUIRE_ERR_NOERR(Result);

	BOOST_TEST_MESSAGE("Control loop enabled. This test runs until the actual value raises above " << Setpoint - 1);
	double ActualValue;
	do
	{
		Result = LCC_ReadActualValue(ControlChannel, &ActualValue);
		BREAK_ON_ERROR(Result);
		BOOST_TEST_MESSAGE("Actual value: " << ActualValue);
		std::this_thread::sleep_for(1s);
	}
	while (ActualValue < (Setpoint - 1));
	REQUIRE_ERR_NOERR(Result);

	// Now we disable the control loop and wait until the temperature dropped
	// by 10 degree
	BOOST_TEST_MESSAGE("Control loop disabled. This test runs until the actual value drops below " << Setpoint - 10);
	Result = LCC_EnableControlLoop(ControlChannel, 0);
	REQUIRE_ERR_NOERR(Result);
	do
	{
		Result = LCC_ReadActualValue(ControlChannel, &ActualValue);
		BREAK_ON_ERROR(Result);
		BOOST_TEST_MESSAGE("Actual value: " << ActualValue);
		std::this_thread::sleep_for(1s);
	}
	while (ActualValue > (Setpoint - 10));
	REQUIRE_ERR_NOERR(Result);
}


//============================================================================
// Checks if C-API can get closed properly
//============================================================================
BOOST_AUTO_TEST_CASE(testCapiClose)
{
	Result = LCB_Stop();
    BOOST_CHECK_EQUAL(ERR_NOERR, Result);

	std::this_thread::sleep_for(2s);
    Result = LCB_Close();
    BOOST_CHECK_EQUAL(ERR_NOERR, Result);
}

//---------------------------------------------------------------------------
// EOF capi_dynamic_controller_test.cpp
