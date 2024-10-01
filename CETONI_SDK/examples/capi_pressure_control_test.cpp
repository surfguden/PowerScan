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
#include <labbcan/c_api/labbCAN_Pump_API.h>
#include <labbcan/common/labbcan_test_helpers.h>

#include <thread>
#include <usl/core/PollingTimer.h>
#include <usl/core/Thread.h>
#include <log4cplus/logger.h>
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
static dev_hdl Pump;


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

	Result = LCAIO_GetInChanHandle(0, &ControlLoopIn);
	REQUIRE_ERR_NOERR(Result);

	Result = LCP_GetPumpHandle(0, &Pump);
	REQUIRE_ERR_NOERR(Result);

	Result = LCC_CreatePIDControlChannel(ControlLoopIn, Pump, PUMP_FLOW, &ControlChannel);
	REQUIRE_ERR_NOERR(Result);
}


//============================================================================
// Build set control channel parameters
//============================================================================
BOOST_AUTO_TEST_CASE(testSetControlParam)
{
	// Now we can set the control channel PID parameters with the values
	// which have been determined in the QmixElements software.
	Result = LCC_SetPIDParameter(ControlChannel, PID_PARAM_K, 0.1);
	REQUIRE_ERR_NOERR(Result);
	Result = LCC_SetPIDParameter(ControlChannel, PID_PARAM_T_D, 0);
	REQUIRE_ERR_NOERR(Result);
	Result = LCC_SetPIDParameter(ControlChannel, PID_PARAM_T_I, 100);
	REQUIRE_ERR_NOERR(Result);
	Result = LCC_SetPIDParameter(ControlChannel, PID_PARAM_DERIVATIVE_GAIN_LIMIT, 0);
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
	Result = LCC_SetPIDParameter(ControlChannel, PID_PARAM_SAMPLE_TIME, 50);
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
// Performs a busy polling to wait until dosage is finished
//============================================================================
bool waitDosageFinished(dev_hdl hPump, uint32_t TimeoutSeconds)
{
	CPollingTimer Timer(TimeoutSeconds * 1000);
	CPollingTimer MessageTimer(500);
	do
	{
		CThread::sleep(100);
		if (MessageTimer.isExpired())
		{
			double FillLevel;
			LCP_GetFillLevel(hPump, &FillLevel);
			BOOST_TEST_MESSAGE("Fill level: " << FillLevel);
			MessageTimer.restart();
		}
		Result = LCP_IsPumping(hPump);
	}
	while ((1 == Result) && !Timer.isExpired());

	return (Result == 0);
}




//============================================================================
// Prepare pump for controller
//============================================================================
BOOST_AUTO_TEST_CASE(testCapiPreparePump)
{
	Result = LCP_SetFlowUnit(Pump, MILLI, LITRES, PER_MINUTE);
	REQUIRE_ERR_NOERR(Result);
	Result = LCP_ClearFault(Pump);
	REQUIRE_ERR_NOERR(Result);
	Result = LCP_Enable(Pump);
	REQUIRE_ERR_NOERR(Result);

	double MaxFlow;
	Result = LCP_GetFlowRateMax(Pump, &MaxFlow);
	REQUIRE_ERR_NOERR(Result);
	Result = LCP_GenerateFlow(Pump, -MaxFlow);
	waitDosageFinished(Pump, 30);
}


//============================================================================
// Checks if start of bus and logging works properly
//============================================================================
BOOST_AUTO_TEST_CASE(testControlLoop)
{
	double Setpoint = 2;

	// Now we write the setpoint and enable the control loop
	Result = LCC_WriteSetPoint(ControlChannel, Setpoint);
	REQUIRE_ERR_NOERR(Result);
	Result = LCC_EnableControlLoop(ControlChannel, 1);
	REQUIRE_ERR_NOERR(Result);

	BOOST_TEST_MESSAGE("Control loop enabled. Loop will run for 60 seconds.");
	double ActualValue;
	double CurrentFlow;
	for (int i = 0; i < 30; ++i)
	{
		Result = LCC_ReadActualValue(ControlChannel, &ActualValue);
		BREAK_ON_ERROR(Result);
		BOOST_TEST_MESSAGE("Actual value: " << ActualValue);
		Result = LCP_GetFlowIs(Pump, &CurrentFlow);
		BREAK_ON_ERROR(Result);
		BOOST_TEST_MESSAGE("Current flow: " << CurrentFlow);
		std::this_thread::sleep_for(1s);
	}
	REQUIRE_ERR_NOERR(Result);

	// Now we disable the control loop
	BOOST_TEST_MESSAGE("Control loop disabled");
	Result = LCC_EnableControlLoop(ControlChannel, 0);
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
