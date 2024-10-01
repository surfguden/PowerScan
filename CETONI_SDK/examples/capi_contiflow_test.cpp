//============================================================================
/// \file   capi_contiflow_test.cpp
/// \author Uwe Kindler
/// \date   21.08.2020
/// \brief  Implementation of 
//============================================================================


//============================================================================
//                                   INCLUDES
//============================================================================
#include <chrono>
#include <vector>

#include <labbcan/c_api/labbCAN_Bus_API.h>
#include <labbcan/c_api/labbCAN_Pump_API.h>
#include <labbcan/c_api/labbCAN_Valve_API.h>
#include <labbcan/common/labbcan_test_helpers.h>

#include <usl/core/Thread.h>
#include <usl/core/PollingTimer.h>
#include <usl/math/uslmath.h>
#include <log4cplus/logger.h>
#include <diag/diag.h>


using namespace Usl;
#define BOOST_TEST_MODULE capi_contiflow_test
#include <boost/test/unit_test.hpp>

//============================================================================
//                               GLOBAL DATA
//============================================================================
dev_hdl ContiFlowPump1;
dev_hdl ContiFlowPump2;
dev_hdl SyringePump1;
dev_hdl SyringePump2;
long Result;


//============================================================================
// Open the labbCAN bus api and connect to device
//============================================================================
BOOST_AUTO_TEST_CASE(testCapiOpen)
{
    Result = LCB_Open("config/contiflow", 0);
    BOOST_REQUIRE_EQUAL(ERR_NOERR, Result);
}


//============================================================================
// Checks if start of bus and logging works properly
//============================================================================
BOOST_AUTO_TEST_CASE(testBusStart)
{
	Result = LCB_Start();
    BOOST_CHECK_EQUAL(Result, ERR_NOERR);
}


//============================================================================
// Test conti flow pump construction
//============================================================================
BOOST_AUTO_TEST_CASE(testContiFlowPumpConstruction)
{
	// First we obtain the device handles for all required devices
	Result = LCP_LookupPumpByName("neMESYS_Low_Pressure_1_Pump", &SyringePump1);
	REQUIRE_ERR_NOERR(Result);

	Result = LCP_LookupPumpByName("neMESYS_Low_Pressure_2_Pump", &SyringePump2);
	REQUIRE_ERR_NOERR(Result);
	
	dev_hdl Valve1;
	Result = LCV_LookupValveByName("neMESYS_Low_Pressure_1_Valve", &Valve1);
	REQUIRE_ERR_NOERR(Result);

	dev_hdl Valve2;
	Result = LCV_LookupValveByName("neMESYS_Low_Pressure_2_Valve", &Valve2);
	REQUIRE_ERR_NOERR(Result);

	// Now we start the construction of the continuous flow pump
	Result = LCP_CreateContiFlowPump(SyringePump1, SyringePump2, &ContiFlowPump1);
	REQUIRE_ERR_NOERR(Result);

	Result = LCP_ConfigureContiFlowValve(ContiFlowPump1, 0, 0, Valve1, 1, 0, -1);
	REQUIRE_ERR_NOERR(Result);

	Result = LCP_ConfigureContiFlowValve(ContiFlowPump1, 1, 0, Valve2, 1, 0, -1);
	REQUIRE_ERR_NOERR(Result);
}


//============================================================================
// Test conti flow pump construction
//============================================================================
BOOST_AUTO_TEST_CASE(testContiFlowPumpConfiguraion)
{
	Result = LCP_SetSyringeParam(SyringePump1, 4.60659, 60);
	REQUIRE_ERR_NOERR(Result);

	Result = LCP_SetSyringeParam(SyringePump2, 4.60659, 60);
	REQUIRE_ERR_NOERR(Result);

	Result = LCP_SetVolumeUnit(ContiFlowPump1, MILLI, LITRES);
	REQUIRE_ERR_NOERR(Result);

	Result = LCP_SetFlowUnit(ContiFlowPump1, MILLI, LITRES, PER_SECOND);
	REQUIRE_ERR_NOERR(Result);
}


//============================================================================
// Setup continuous flow pump
//============================================================================
void setupContiFlowParameters(dev_hdl ContiFlowPump, double CrossFlowSecs)
{
	// At the moment only cross flow is supported
	Result = LCB_SetDeviceProperty(ContiFlowPump, PropertySwitchingMode, SwitchingCrossFlow);
	REQUIRE_ERR_NOERR(Result);

	double MaxRefillFlow;
	Result = LCB_GetDeviceProperty(ContiFlowPump, PropertyMaxRefillFlow, &MaxRefillFlow);
	REQUIRE_ERR_NOERR(Result);

	BOOST_TEST_MESSAGE("MaxRefilFlow: " << MaxRefillFlow);
	Result = LCB_SetDeviceProperty(ContiFlowPump, PropertyRefillFlow, MaxRefillFlow / 2.0);
	REQUIRE_ERR_NOERR(Result);

	Result = LCB_SetDeviceProperty(ContiFlowPump, PropertyCrossFlowDuration_s, CrossFlowSecs);
	REQUIRE_ERR_NOERR(Result);

	Result = LCB_SetDeviceProperty(ContiFlowPump, PropertyOverlapDuration_s, 0.0);
	REQUIRE_ERR_NOERR(Result);

	double MaxContiFlowRate;
	Result = LCP_GetFlowRateMax(ContiFlowPump, &MaxContiFlowRate);
	REQUIRE_ERR_NOERR(Result);

	BOOST_TEST_MESSAGE("MaxContiFlowRate: " << MaxContiFlowRate);
}


//============================================================================
// Test conti flow pump parameter setting
//============================================================================
BOOST_AUTO_TEST_CASE(testContiFlowParameters)
{
	setupContiFlowParameters(ContiFlowPump1, 2);
}


//============================================================================
// Performs a busy polling to wait until calibration is finished
//============================================================================
bool waitCalibrationFinished(dev_hdl hPump, uint32_t TimeoutSeconds)
{
	CPollingTimer Timer(TimeoutSeconds * 1000);
	do
	{
		CThread::sleep(100);
		Result = LCP_IsCalibrationFinished(hPump);
	}
	while ((0 == Result) && !Timer.isExpired());

	return (Result > 0);
}


//============================================================================
// Performs a busy polling to wait until calibration is finished
//============================================================================
bool waitInitializationFinished(dev_hdl hPump, uint32_t TimeoutSeconds)
{
	CPollingTimer Timer(TimeoutSeconds * 1000);
	do
	{
		CThread::sleep(100);
		Result = LCP_IsContiFlowInitializing(hPump);
	}
	while ((1 == Result) && !Timer.isExpired());

	Result = LCP_IsContiFlowInitialized(hPump);
	return (Result > 0);
}


//============================================================================
// Test conti flow pump enable
//============================================================================
BOOST_AUTO_TEST_CASE(testContiFlowEnable)
{
	Result = LCP_ClearFault(ContiFlowPump1);
	REQUIRE_ERR_NOERR(Result);

	Result = LCP_Enable(ContiFlowPump1);
	REQUIRE_ERR_NOERR(Result);
}


//============================================================================
// Test initialization of conti flow
//============================================================================
BOOST_AUTO_TEST_CASE(testContiFlowInit)
{
	dev_hdl SyringePump0;
	Result = LCP_GetContiFlowSyringePump(ContiFlowPump1, 0, &SyringePump0);
	REQUIRE_ERR_NOERR(Result);
	Result = LCP_SyringePumpCalibrate(SyringePump0);
	REQUIRE_ERR_NOERR(Result);

	dev_hdl SyringePump1;
	Result = LCP_GetContiFlowSyringePump(ContiFlowPump1, 1, &SyringePump1);
	REQUIRE_ERR_NOERR(Result);
	Result = LCP_SyringePumpCalibrate(SyringePump1);
	REQUIRE_ERR_NOERR(Result);

    bool CalibrationFinished = waitCalibrationFinished(SyringePump0, 30);
	BOOST_CHECK(CalibrationFinished);
	CalibrationFinished = waitCalibrationFinished(SyringePump1, 30);
	BOOST_CHECK(CalibrationFinished);

	Result = LCP_InitializeContiFlow(ContiFlowPump1);
	REQUIRE_ERR_NOERR(Result);
	bool InitializationFinished = waitInitializationFinished(ContiFlowPump1, 30);
	BOOST_REQUIRE(InitializationFinished);
}


//============================================================================
// Test continuous flow
//============================================================================
BOOST_AUTO_TEST_CASE(testContiFlow)
{
	double MaxContiFlowRate;
	Result = LCP_GetFlowRateMax(ContiFlowPump1, &MaxContiFlowRate);
	REQUIRE_ERR_NOERR(Result);

	Result = LCP_GenerateFlow(ContiFlowPump1, MaxContiFlowRate);
	REQUIRE_ERR_NOERR(Result);

	BOOST_TEST_MESSAGE("Starting flow with flow rate: " << MaxContiFlowRate);
	CPollingTimer Timer(30 * 1000);
	do
	{
		CThread::sleep(1000);
		double CurrentFlow;
		Result = LCP_GetFlowIs(ContiFlowPump1, &CurrentFlow);
		BOOST_TEST_MESSAGE("Current flow rate: " << CurrentFlow
			<< "  Remaining seconds: " << Timer.msecsToExpiration() / 1000);
	}
	while (!Timer.isExpired());

	BOOST_TEST_MESSAGE("Starting flow with flow rate: " << MaxContiFlowRate / 2);
	Result = LCP_GenerateFlow(ContiFlowPump1, MaxContiFlowRate / 2);
	Timer.setPeriod(34 * 1000);
	Timer.restart();
	REQUIRE_ERR_NOERR(Result);
	do
	{
		CThread::sleep(1000);
		double CurrentFlow;
		Result = LCP_GetFlowIs(ContiFlowPump1, &CurrentFlow);
		BOOST_TEST_MESSAGE("Current flow rate: " << CurrentFlow
			<< "  Remaining seconds: " << Timer.msecsToExpiration() / 1000);
	}
	while (!Timer.isExpired());

	Result = LCP_StopPumping(ContiFlowPump1);
	REQUIRE_ERR_NOERR(Result);
	CThread::sleep(1000);
}


//============================================================================
// Test volume dosing in continuous flow
//============================================================================
BOOST_AUTO_TEST_CASE(testDeviceLookup)
{
	Result = LCP_LookupPumpByName("ContiFlowPump_1", &ContiFlowPump2);
	REQUIRE_ERR_NOERR(Result);

	setupContiFlowParameters(ContiFlowPump2, 1);

	Result = LCP_IsContiFlowInitialized(ContiFlowPump2);
	REQUIRE_ERR_NOERR(Result);
	if (0 == Result)
	{
		Result = LCP_InitializeContiFlow(ContiFlowPump2);
		REQUIRE_ERR_NOERR(Result);
	}
}


//============================================================================
// Test volume dosing in continuous flow
//============================================================================
BOOST_AUTO_TEST_CASE(testContiFlowVolumeDosing)
{
	dev_hdl ContiFlowPump = ContiFlowPump2;

	dev_hdl SyringePump0;
	Result = LCP_GetContiFlowSyringePump(ContiFlowPump, 0, &SyringePump0);
	REQUIRE_ERR_NOERR(Result);

	double MaxSyringeLevel;
	Result = LCP_GetVolumeMax(SyringePump0, &MaxSyringeLevel);
	REQUIRE_ERR_NOERR(Result);

	double MaxContiFlowRate;
	Result = LCP_GetFlowRateMax(ContiFlowPump, &MaxContiFlowRate);
	REQUIRE_ERR_NOERR(Result);

	double TargetVolume = MaxSyringeLevel * 1.5;
	Result = LCP_PumpVolume(ContiFlowPump, TargetVolume, MaxContiFlowRate);
	REQUIRE_ERR_NOERR(Result);

	CPollingTimer Timer(60 * 1000);
	do
	{
		CThread::sleep(1000);
		double DosedVolume;
		Result = LCP_GetDosedVolume(ContiFlowPump, &DosedVolume);
		BOOST_TEST_MESSAGE("Dosed volume: " << DosedVolume << " Target volume: " << TargetVolume);
		Result = LCP_IsPumping(ContiFlowPump);
	}
	while (1 == Result && !Timer.isExpired());
}


//============================================================================
// Checks if C-API can get closed properly
//============================================================================
BOOST_AUTO_TEST_CASE(testCapiClose)
{
	Result = LCB_Stop();
    BOOST_CHECK_EQUAL(ERR_NOERR, Result);

    Result = LCB_Close();
    BOOST_CHECK_EQUAL(ERR_NOERR, Result);
}


//---------------------------------------------------------------------------
// EOF capi_contiflow_test.cpp
