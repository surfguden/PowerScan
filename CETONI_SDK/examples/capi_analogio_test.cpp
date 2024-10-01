//============================================================================
/// \file   capi_analogio_test.cpp
/// \author Uwe Kindler
/// \date   11.06.2018
/// \brief  Implementation of some tests for labbCAN analog I/O API
//============================================================================


//============================================================================
//                                   INCLUDES
//============================================================================
#include <labbcan/c_api/labbCAN_Bus_API.h>
#include <labbcan/c_api/labbCAN_AnalogIO_API.h>
#include <labbcan/common/labbcan_test_helpers.h>

#include <thread>
#include <usl/core/PollingTimer.h>
#include <diag/diag.h>
#include <iostream>


//using namespace Lcl;
using namespace std::chrono_literals;
using namespace Usl;
#define BOOST_TEST_MODULE capi_analogio_test.cpp
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


static dev_hdl AnalogIn;
static dev_hdl AnalogOut;


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
// Test channel lookup
//============================================================================
BOOST_AUTO_TEST_CASE(testChannelLookup)
{
	Result = LCAIO_LookupInChanByName("QmixIO_1_AI0", &AnalogIn);
	REQUIRE_ERR_NOERR(Result);

	Result = LCAIO_LookupOutChanByName("QmixIO_1_AO0_PWM", &AnalogOut);
	REQUIRE_ERR_NOERR(Result);
}


//============================================================================
// Tests I/O device retrieval
//============================================================================
BOOST_AUTO_TEST_CASE(testIoDevice)
{
	dev_hdl IoDevice;
	Result = LCAIO_GetAnalogIoDevice(AnalogIn, &IoDevice);
	CHECK_RETURN_CODE(Result)
	char DeviceName[256];
	Result = LCB_GetDevName(IoDevice, DeviceName, sizeof(DeviceName));
	CHECK_RETURN_CODE(Result)
	BOOST_TEST_MESSAGE("Analog In device name: " << DeviceName);

	Result = LCAIO_GetAnalogIoDevice(AnalogOut, &IoDevice);
	CHECK_RETURN_CODE(Result)
	Result = LCB_GetDevName(IoDevice, DeviceName, sizeof(DeviceName));
	CHECK_RETURN_CODE(Result)
	BOOST_TEST_MESSAGE("Analog Out device name: " << DeviceName);
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
// EOF capi_analogio_test.cpp
