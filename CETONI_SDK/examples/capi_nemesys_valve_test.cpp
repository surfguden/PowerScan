//============================================================================
/// \file   capi_nemesys_valve_test.cpp
/// \author Uwe Kindler
/// \date   13.07.2012
/// \brief  Test of labbCAN valve API
//============================================================================


//============================================================================
//                                   INCLUDES
//============================================================================
#include <labbcan/c_api/labbCAN_Bus_API.h>
#include <labbcan/c_api/labbCAN_Valve_API.h>
#include <labbcan/c_api/labbCAN_Pump_API.h>

#include <string>

#include <usl/core/Thread.h>
#include <usl/core/PollingTimer.h>
#include <log4cplus/logger.h>
#include <diag/diag.h>


using namespace Usl;
#define BOOST_TEST_MODULE capi_nemesys_valve_test
#include <boost/test/unit_test.hpp>


//============================================================================
//                                DATA TYPES
//============================================================================



//============================================================================
//                               GLOBAL DATA
//============================================================================
dev_hdl hValve1;
long Result;


//============================================================================
// Open the labbCAN bus api and connect to device
//============================================================================
BOOST_AUTO_TEST_CASE(testCapiOpen)
{
    Result = LCB_Open("config/testconfig_qmixsdk", 0);
    BOOST_REQUIRE_EQUAL(ERR_NOERR, Result);
}


//============================================================================
// Checks if retrieval of pump devices works properly
//============================================================================
BOOST_AUTO_TEST_CASE(testDeviceNameLookup)
{
	Result = LCV_LookupValveByName("neMESYS_Low_Pressure_1_Valve", &hValve1);
    BOOST_CHECK_NE(hValve1, 0);
    BOOST_CHECK_EQUAL(Result, ERR_NOERR);

    char ValveName[64];
    Result = LCB_GetDevName(hValve1, ValveName, sizeof(ValveName));
    BOOST_CHECK_EQUAL(Result, ERR_NOERR);
    BOOST_TEST_MESSAGE("Valve name: " << ValveName);

    dev_hdl hValve;
    Result = LCV_GetValveHandle(1, &hValve);
    BOOST_CHECK_EQUAL(Result, ERR_NOERR);
    Result = LCB_GetDevName(hValve, ValveName, sizeof(ValveName));
    BOOST_CHECK_EQUAL(Result, ERR_NOERR);
    BOOST_TEST_MESSAGE("Valve name: " << ValveName);

    dev_hdl hPump1;
    Result = LCP_LookupPumpByName("neMESYS_Low_Pressure_1_Pump", &hPump1);
    BOOST_CHECK_NE(hPump1, 0);
    BOOST_CHECK_EQUAL(Result, ERR_NOERR);

    long HasValve = LCP_HasValve(hPump1);
    BOOST_CHECK_EQUAL(HasValve, 1);

    dev_hdl hValve2;
    Result = LCP_GetValveHandle(hPump1, &hValve2);
    BOOST_CHECK_EQUAL(Result, ERR_NOERR);
    Result = LCB_GetDevName(hValve2, ValveName, sizeof(ValveName));
    BOOST_CHECK_EQUAL(Result, ERR_NOERR);
    BOOST_TEST_MESSAGE("Valve name: " << ValveName);
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
    CThread::sleep(2000); // give devices some time to process
}


//============================================================================
// Valve control test
//============================================================================
BOOST_AUTO_TEST_CASE(testValveControl)
{
	long NumberOfValvePositions = LCV_NumberOfValvePositions(hValve1);
    BOOST_CHECK_GT(NumberOfValvePositions, 0);
    BOOST_TEST_MESSAGE("Valve positions: " << NumberOfValvePositions);

    for (int i = 0; i < NumberOfValvePositions; ++i)
    {
    	Result = LCV_SwitchValveToPosition(hValve1, i);
    	BOOST_CHECK_EQUAL(Result, ERR_NOERR);
        CThread::sleep(2000); // give valve some time to move to target
    	Result = LCV_ActualValvePosition(hValve1);
    	BOOST_CHECK_EQUAL(Result, i);
    }
    CThread::sleep(2000); // give devices some time to process
}


//============================================================================
// Checks if C-API can get closed properly
//============================================================================
BOOST_AUTO_TEST_CASE(testCapiClose)
{
	Result = LCB_Stop();
    BOOST_CHECK_EQUAL(ERR_NOERR, Result);

	CThread::sleep(2000); // give devices some time to process
    Result = LCB_Close();
    BOOST_CHECK_EQUAL(ERR_NOERR, Result);
}


//---------------------------------------------------------------------------
// EOF capi_test.cpp
