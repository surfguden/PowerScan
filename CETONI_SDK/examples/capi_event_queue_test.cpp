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
#include <iostream>
#include <cmath>

#include <usl/core/PollingTimer.h>
#include <usl/core/Thread.h>
#include <log4cplus/logger.h>
#include <diag/diag.h>


//using namespace Lcl;
using namespace std::chrono_literals;
using namespace Usl;
#define BOOST_TEST_MODULE capi_device_retrival_test
#include <boost/test/unit_test.hpp>

using namespace boost::unit_test;

/**
* Make available program's arguments to all tests, receiving
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
    Result = LCB_Start();
    REQUIRE_ERR_NOERR(Result);
    Result = LCP_GetPumpHandle(0, &Pump);
    REQUIRE_ERR_NOERR(Result);
}


//============================================================================
/**
 * Structure for reading event via LCB_ReadEventEx()
 */
struct tEvent
{
	long Id;
	dev_hdl Device;
	long Data[2];
	char EventString[256];
};


//============================================================================
/**
 * Handles event LCB_EVENT_DEVICE_EMERGENCY - device emergency events
 */
void handleDeviceEmergencyEvent(const tEvent& Event)
{
	char DeviceName[64];
	Result = LCB_GetDevName(Event.Device, DeviceName, sizeof(DeviceName));
	CHECK_RETURN_CODE(Result);

	char ErrorMessage[128];
	Result = LCB_GetDevErrMsg(Event.Device, Event.Data[0], ErrorMessage, sizeof(ErrorMessage));
	CHECK_RETURN_CODE(Result);
	std::cout << "Device " << DeviceName << " emitted emergency event 0x"
		<< std::hex << Event.Data[0] << std::dec << " - " << ErrorMessage << std::endl;
}


//============================================================================
/**
 * Handles event LCB_EVENT_DATA_LINK_LAYER
 */
void handleDataLinkLayerEvent(const tEvent& Event)
{
	char ErrorMessage[128];
	Result = LCB_GetErrMsg(Event.Data[0], ErrorMessage, sizeof(ErrorMessage));
	CHECK_RETURN_CODE(Result);
	std::cout << "Data link layer error 0x"
		<< std::hex << abs(Event.Data[0]) << std::dec << " - " << ErrorMessage << std::endl;
}


//============================================================================
/**
 * Handles event LCB_EVENT_DEVICE_GUARD
 */
void handleDeviceGuardEvent(const tEvent& Event)
{
	char DeviceName[64];
	Result = LCB_GetDevName(Event.Device, DeviceName, sizeof(DeviceName));
	CHECK_RETURN_CODE(Result);

	std::string EventString = "Device guard event from device ";
	EventString += DeviceName;
	EventString += ": ";
	switch (Event.Data[0])
	{
	case NODEGUARD_ERR_OCCURED: EventString += "node guarding error occurred"; break;
	case NODEGUARD_ERR_RESOLVED: EventString += "node guarding error resolved"; break;
	case HEARTBEAT_ERR_OCCURED: EventString += "heartbeat error occurred"; break;
	case HEARTBEAT_ERR_RESOLVED: EventString += "heartbeat error resolved"; break;
	case NODESTATE_ERR: EventString += "node state error"; break;
	case NODESTATE_CHANGED: EventString += "node state changed"; break;
	}
	std::cout << EventString << std::endl;
}


//============================================================================
// Checks if C-API can get closed properly
//============================================================================
BOOST_AUTO_TEST_CASE(testEventQueue)
{
	tEvent Event;
	// Run this test for 60 seconds
	CPollingTimer TimeoutTimer(60000);
	while (!TimeoutTimer.isExpired())
	{
		Result = LCB_ReadEventEx(&Event.Id, &Event.Device, &Event.Data[0], &Event.Data[1],
			Event.EventString, sizeof(Event.EventString));
		if (-ERR_AGAIN == Result)
		{
			BOOST_TEST_MESSAGE("Event queue is empty");
			std::cout << "Event queue is empty" << std::endl;
			std::this_thread::sleep_for(1s);
			continue;
		}

		if (ERR_NOERR != Result)
		{
			BOOST_FAIL("Error reading event queue");
		}

		BOOST_TEST_MESSAGE("Received event");
		std::cout << Event.EventString << std::endl;
		switch (Event.Id)
		{
		case LCB_EVENT_DEVICE_EMERGENCY: handleDeviceEmergencyEvent(Event); break;
		case LCB_EVENT_DATA_LINK_LAYER: handleDataLinkLayerEvent(Event); break;
		case LCB_EVENT_DEVICE_GUARD: handleDeviceGuardEvent(Event); break;
		}
	}
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
