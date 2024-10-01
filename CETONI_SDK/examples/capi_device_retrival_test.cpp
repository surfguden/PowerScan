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
using namespace Usl;
#define BOOST_TEST_MODULE capi_device_retrival_test
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
// Test pump device handles
//============================================================================
BOOST_AUTO_TEST_CASE(testPumpDeviceHandles)
{
	dev_hdl Pump;
	auto NumberOfPumps = LCP_GetNoOfPumps();
	BOOST_CHECK(NumberOfPumps >= 0);
	BOOST_TEST_MESSAGE("Number of pumps " << NumberOfPumps);
	for (int i = 0; i < NumberOfPumps; ++i)
	{
		char PumpName[64];
		Result = LCP_GetPumpHandle(i, &Pump);
		CHECK_RETURN_CODE(Result);
		Result = LCP_GetPumpName(Pump, PumpName, sizeof(PumpName));
		CHECK_RETURN_CODE(Result);
		Result = LCB_GetDevName(Pump, PumpName, sizeof(PumpName));
		CHECK_RETURN_CODE(Result);
		BOOST_TEST_MESSAGE("Name of pump " << i << ": " << PumpName);
		dev_hdl NamedPump;
		Result = LCP_LookupPumpByName(PumpName, &NamedPump);
		CHECK_RETURN_CODE(Result);
		BOOST_CHECK_EQUAL(Pump, NamedPump);
	}
}

//============================================================================
// Test Qmix P device handles
//============================================================================
BOOST_AUTO_TEST_CASE(testQmixpChannelHandles)
{
	dev_hdl AnalogIn;

	auto NumberOfChannels = LCAIO_GetNoOfInputChannels();
	BOOST_CHECK(NumberOfChannels >= 0);
	BOOST_TEST_MESSAGE("Number of analog input channels " << NumberOfChannels);
	if (NumberOfChannels <= 0)
	{
		return;
	}

	for (int i = 0; i < NumberOfChannels; ++i)
	{
		char Name[64];
		Result = LCAIO_GetInChanHandle(i, &AnalogIn);
		CHECK_RETURN_CODE(Result);
		Result = LCAIO_GetChanName(AnalogIn, Name, sizeof(Name));
		CHECK_RETURN_CODE(Result);
		BOOST_TEST_MESSAGE("Name of analog input channel " << i << ": " << Name);
		dev_hdl NamedAnalogIn;
		LCAIO_LookupInChanByName(Name, &NamedAnalogIn);
		CHECK_RETURN_CODE(Result);
		BOOST_CHECK_EQUAL(AnalogIn, NamedAnalogIn);
	}
}

//============================================================================
// Test Qmix TC controller device handles
//============================================================================
BOOST_AUTO_TEST_CASE(testControllerHandles)
{
	dev_hdl Controller;
	auto NumberOfChannels = LCC_GetNoOfControlChannels();
	BOOST_CHECK(NumberOfChannels >= 0);
	if (NumberOfChannels <= 0)
	{
		return;
	}

	BOOST_TEST_MESSAGE("Number of control channels " << NumberOfChannels);
	for (int i = 0; i < NumberOfChannels; ++i)
	{
		char Name[64];
		Result = LCC_GetChannelHandle(i, &Controller);
		CHECK_RETURN_CODE(Result);
		Result = LCC_GetChanName(Controller, Name, sizeof(Name));
		CHECK_RETURN_CODE(Result);
		BOOST_TEST_MESSAGE("Name of control channel " << i << ": " << Name);
		dev_hdl NamedController;
		Result = LCC_LookupChanByName(Name, &NamedController);
		CHECK_RETURN_CODE(Result);
		BOOST_CHECK_EQUAL(Controller, NamedController);
	}
}


//---------------------------------------------------------------------------
// EOF capi_dynamic_controller_test.cpp
