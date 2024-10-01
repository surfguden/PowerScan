//============================================================================
/// \file   capi_qmixqplus_test.cpp
/// \author Uwe Kindler
/// \date   26.04.2018
/// \brief  Test shows how to access the QmixQ+ control channels
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
#define BOOST_TEST_MODULE capi_qmixqplus_test.cpp
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


dev_hdl ReactorZone;
dev_hdl ReactionLoop;


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
// Checks if retrieval of controller channels work properly
// You need to know the name of the controller channel. You will find it
// in the controller XML file
//============================================================================
BOOST_AUTO_TEST_CASE(testDeviceNameLookup)
{
	Result = LCC_LookupChanByName("QmixQplus_1_ReactorZone", &ReactorZone);
	REQUIRE_ERR_NOERR(Result);

	Result = LCC_LookupChanByName("QmixQplus_1_ReactionLoop", &ReactionLoop);
	REQUIRE_ERR_NOERR(Result);
}


//============================================================================
// Checks if retrieval of controller channels via index works properly
//============================================================================
BOOST_AUTO_TEST_CASE(testChanneEnumeration)
{
	long ChannelCount  = LCC_GetNoOfControlChannels();
	BOOST_CHECK_GT(ChannelCount, -1);

	for (long i = 0; i < ChannelCount; ++i)
	{
		dev_hdl Channel;
		Result = LCC_GetChannelHandle(i, &Channel);
		REQUIRE_ERR_NOERR(Result);

		char ChannelName[128];
		Result = LCC_GetChanName(Channel, ChannelName, sizeof(ChannelName));
		REQUIRE_ERR_NOERR(Result);

		std::cout << "Channel[" << i << "]: " << ChannelName << std::endl;
	}
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
// Checks if enabling control loop and reading enable status works
//============================================================================
BOOST_AUTO_TEST_CASE(testControlLoopEnable)
{
	double Setpoint = 40;
	// Now we write the setpoint and enable the control loop
	Result = LCC_WriteSetPoint(ReactionLoop, Setpoint);
	REQUIRE_ERR_NOERR(Result);

	Result = LCC_EnableControlLoop(ReactionLoop, 1);
	REQUIRE_ERR_NOERR(Result);

	Result = LCC_IsControlLoopEnabled(ReactionLoop);
	CHECK_RETURN_CODE(Result);
	BOOST_CHECK(1 == Result);

	Result = LCC_EnableControlLoop(ReactionLoop, 0);
	REQUIRE_ERR_NOERR(Result);

	Result = LCC_IsControlLoopEnabled(ReactionLoop);
	CHECK_RETURN_CODE(Result);
	BOOST_CHECK(0 == Result);
}


//============================================================================
// Checks if the control loop works properly
//============================================================================
BOOST_AUTO_TEST_CASE(testControlLoopHeatingUp)
{
	double Setpoint = 40;

	Result = LCC_EnableControlLoop(ReactionLoop, 1);
	REQUIRE_ERR_NOERR(Result);
	BOOST_TEST_MESSAGE("Control loop enabled. This test runs until the actual value raises above " << Setpoint - 1);
	double ReactorZoneValue;
	double ReactionLoopValue;
	do
	{
		// We display the temperature of both control loops - one should
		// raise and one should remain constant
		Result = LCC_ReadActualValue(ReactorZone, &ReactorZoneValue);
		BREAK_ON_ERROR(Result);
		Result = LCC_ReadActualValue(ReactionLoop, &ReactionLoopValue);
		BREAK_ON_ERROR(Result);
		BOOST_TEST_MESSAGE("Actual values: Reaction Loop = " << ReactionLoopValue
			<< "  Reactor Zone = " << ReactorZoneValue);
		std::this_thread::sleep_for(1s);
	}
	while (ReactionLoopValue < (Setpoint - 1));
	REQUIRE_ERR_NOERR(Result);

	// Now we disable the control loop and wait until the temperature dropped
	// by 10 degree
	Result = LCC_EnableControlLoop(ReactionLoop, 0);
	REQUIRE_ERR_NOERR(Result);
	BOOST_TEST_MESSAGE("Control loop disabled. This test runs until the actual value drops below " << Setpoint - 5);
	do
	{
		Result = LCC_ReadActualValue(ReactionLoop, &ReactionLoopValue);
		BREAK_ON_ERROR(Result);
		BOOST_TEST_MESSAGE("Reaction Loop Actual value: " << ReactionLoopValue);
		std::this_thread::sleep_for(1s);
	}
	while (ReactionLoopValue > (Setpoint - 5));
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
