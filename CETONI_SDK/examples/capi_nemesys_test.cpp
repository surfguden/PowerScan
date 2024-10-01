//============================================================================
/// \file   capi_nemesys_test.cpp
/// \author Uwe Kindler
/// \date   11.07.2012
/// \brief  Test of labbCAN pump API
//============================================================================


//============================================================================
//                                   INCLUDES
//============================================================================
#include <chrono>
#include <vector>

#include <labbcan/c_api/labbCAN_Bus_API.h>
#include <labbcan/c_api/labbCAN_Pump_API.h>
#include <labbcan/c_api/labbCAN_Valve_API.h>
#include <labbcan/c_api/labbCAN_MotionControl_API.h>
#include <labbcan/common/labbcan_test_helpers.h>

#include <usl/core/Thread.h>
#include <usl/core/PollingTimer.h>
#include <usl/math/uslmath.h>
#include <log4cplus/logger.h>
#include <diag/diag.h>


using namespace Usl;
#define BOOST_TEST_MODULE capi_nemesys_test
#include <boost/test/unit_test.hpp>


//============================================================================
//                                DATA TYPES
//============================================================================



//============================================================================
//                               GLOBAL DATA
//============================================================================
dev_hdl hNemesys1;
dev_hdl hNemesys1Axis;
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
	std::string PumpName = "neMESYS_Low_Pressure_1_Pump";
	Result = LCP_LookupPumpByName(PumpName.c_str(), &hNemesys1);
    BOOST_CHECK_NE(hNemesys1, 0);
    BOOST_CHECK_EQUAL(Result, ERR_NOERR);

    dev_hdl hPump;
    int IndexOfPump = -1;
    Result = LCP_GetNoOfPumps();
    BOOST_CHECK_GT(Result, 0);
    long PumpCount = Result;
    // Prints names of all pumps and stores the index of the pump that we
    // have just looked up by name
    for (int i = 0; i < PumpCount; ++i)
    {
    	Result = LCP_GetPumpHandle(i, &hPump);
    	BOOST_CHECK_EQUAL(Result, ERR_NOERR);
    	char NameBuf[128];
    	Result = LCP_GetPumpName(hPump, NameBuf, sizeof(NameBuf));
    	BOOST_CHECK_EQUAL(Result, ERR_NOERR);
    	std::string Name(NameBuf);
    	if (PumpName == Name)
    	{
    		IndexOfPump = i;
    		BOOST_CHECK_EQUAL(hNemesys1, hPump);
    	}
    	BOOST_TEST_MESSAGE("Name of pump " << i << ": " << Name);
    }

    BOOST_CHECK_GT(IndexOfPump, -1);
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
// Checks if enabling pumps works properly
//============================================================================
BOOST_AUTO_TEST_CASE(testPumpEnable)
{
	Result = LCP_IsInFaultState(hNemesys1);
	BOOST_CHECK_GT(Result, -1);
	if (Result)
	{
		Result = LCP_ClearFault(hNemesys1);
		BOOST_CHECK_EQUAL(Result, ERR_NOERR);
	}
	Result = LCP_Enable(hNemesys1);
	BOOST_CHECK_EQUAL(Result, ERR_NOERR);
	CThread::sleep(500);// give pump some time to process enable request
	Result = LCP_IsEnabled(hNemesys1);
	BOOST_CHECK_GT(Result, 0);
}


//============================================================================
// Checks if start of bus and logging works properly
//============================================================================
BOOST_AUTO_TEST_CASE(testApirate)
{
    Result = LCP_Aspirate(hNemesys1, 1, 7);
    BOOST_CHECK_EQUAL(Result, ERR_NOERR);
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
// Tests if reference move of syringe pump works properly
//============================================================================
BOOST_AUTO_TEST_CASE(testCalibration)
{
	Result = LCP_IsCalibrationFinished(hNemesys1);

	Result = LCP_SyringePumpCalibrate(hNemesys1);
	BOOST_CHECK_EQUAL(Result, ERR_NOERR);
	CThread::sleep(200);
	bool CalibrationFinished = waitCalibrationFinished(hNemesys1, 30);
	BOOST_CHECK(CalibrationFinished);
}


//============================================================================
// Checks if configuration of syringe parameters works properly
//============================================================================
BOOST_AUTO_TEST_CASE(testSyringeConfig)
{
	double InnerDiameterSet = 1;
	double PistonStrokeSet = 60;
	Result = LCP_SetSyringeParam(hNemesys1, InnerDiameterSet, PistonStrokeSet);
	BOOST_CHECK_EQUAL(ERR_NOERR, Result);

	BOOST_TEST_MESSAGE("Set syringe inner diameter: " << InnerDiameterSet
		<< ", piston stroke: " << PistonStrokeSet);

	double InnerDiameterGet;
	double PistonStrokeGet;
	Result = LCP_GetSyringeParam(hNemesys1, &InnerDiameterGet, &PistonStrokeGet);
	BOOST_CHECK_EQUAL(ERR_NOERR, Result);

	BOOST_TEST_MESSAGE("Get syringe inner diameter: " << InnerDiameterGet
		<< ", piston stroke: " << PistonStrokeGet);

	BOOST_CHECK_EQUAL(InnerDiameterSet, InnerDiameterGet);
	BOOST_CHECK_EQUAL(PistonStrokeSet, PistonStrokeGet);
}


//============================================================================
// Checks if SI unit handling works properly
//============================================================================
BOOST_AUTO_TEST_CASE(testSiUnits)
{
	Result = LCP_SetVolumeUnit(hNemesys1, MILLI, LITRES);
	BOOST_CHECK_EQUAL(ERR_NOERR, Result);

	double MaxMillilitres;
	Result = LCP_GetVolumeMax(hNemesys1, &MaxMillilitres);
	BOOST_CHECK_EQUAL(ERR_NOERR, Result);

	Result = LCP_SetVolumeUnit(hNemesys1, UNIT, LITRES);
	BOOST_CHECK_EQUAL(ERR_NOERR, Result);

	double MaxLitres;
	Result = LCP_GetVolumeMax(hNemesys1, &MaxLitres);
	BOOST_CHECK_EQUAL(ERR_NOERR, Result);

	BOOST_CHECK(Usl::approximatelyEqual(MaxMillilitres, MaxLitres * 1000));
	BOOST_TEST_MESSAGE("MaxMillilitres:" << MaxMillilitres << "  MaxLitres: "
		<< MaxLitres);

	Result = LCP_SetFlowUnit(hNemesys1, MILLI, LITRES, PER_SECOND);
	BOOST_CHECK_EQUAL(ERR_NOERR, Result);

	double MaxMillilitresPerSecond;
	Result = LCP_GetFlowRateMax(hNemesys1, &MaxMillilitresPerSecond);
	BOOST_CHECK_EQUAL(ERR_NOERR, Result);

	Result = LCP_SetFlowUnit(hNemesys1, MILLI, LITRES, PER_MINUTE);
	BOOST_CHECK_EQUAL(ERR_NOERR, Result);

	double MaxMillilitresPerMinute;
	Result = LCP_GetFlowRateMax(hNemesys1, &MaxMillilitresPerMinute);
	BOOST_CHECK_EQUAL(ERR_NOERR, Result);

	BOOST_CHECK_EQUAL(MaxMillilitresPerSecond * 60, MaxMillilitresPerMinute);
	BOOST_TEST_MESSAGE("MaxMillilitresPerSecond:" << MaxMillilitresPerSecond
		<< "  MaxMillilitresPerMinute: " << MaxMillilitresPerMinute);

	Result = LCP_SetFlowUnit(hNemesys1, UNIT, LITRES, PER_MINUTE);
	BOOST_CHECK_EQUAL(ERR_NOERR, Result);

	double MaxLitresPerMinute;
	Result = LCP_GetFlowRateMax(hNemesys1, &MaxLitresPerMinute);
	BOOST_CHECK_EQUAL(ERR_NOERR, Result);

	BOOST_CHECK(Usl::approximatelyEqual(MaxMillilitresPerMinute, MaxLitresPerMinute * 1000));
	BOOST_TEST_MESSAGE("MaxMillilitresPerMinute: " << MaxMillilitresPerMinute
		<< "MaxLitresPerMinute: " << MaxLitresPerMinute);
}



//============================================================================
// Checks if aspiration works properly
//============================================================================
BOOST_AUTO_TEST_CASE(testAspirate)
{
	double MaxVolume;
	double MaxFlow;

	Result = LCP_GetVolumeMax(hNemesys1, &MaxVolume);
	BOOST_CHECK_EQUAL(ERR_NOERR, Result);
	MaxVolume /= 2;

	Result = LCP_GetFlowRateMax(hNemesys1, &MaxFlow);
	BOOST_CHECK_EQUAL(ERR_NOERR, Result);

	Result = LCP_Aspirate(hNemesys1, MaxVolume, MaxFlow);
    BOOST_CHECK_EQUAL(ERR_NOERR, Result);
    bool PumpingFinished = waitDosageFinished(hNemesys1, 30);
	BOOST_CHECK(PumpingFinished);
}


//============================================================================
// Checks if dispension works properly
//============================================================================
BOOST_AUTO_TEST_CASE(testDispense)
{
	double MaxVolume;
	double MaxFlow;

	Result = LCP_GetVolumeMax(hNemesys1, &MaxVolume);
	BOOST_CHECK_EQUAL(ERR_NOERR, Result);
	MaxVolume /= 10;

	Result = LCP_GetFlowRateMax(hNemesys1, &MaxFlow);
	BOOST_CHECK_EQUAL(ERR_NOERR, Result);
	MaxFlow /= 2;

	Result = LCP_Dispense(hNemesys1, MaxVolume, MaxFlow);
    BOOST_CHECK_EQUAL(ERR_NOERR, Result);
    bool PumpingFinished = waitDosageFinished(hNemesys1, 20);
	BOOST_CHECK(PumpingFinished);
}


//============================================================================
// Checks if pumping works properly
//============================================================================
BOOST_AUTO_TEST_CASE(testPumpVolume)
{
	double MaxVolume;
	double MaxFlow;

	Result = LCP_GetVolumeMax(hNemesys1, &MaxVolume);
	BOOST_CHECK_EQUAL(ERR_NOERR, Result);
	MaxVolume /= 10;

	Result = LCP_GetFlowRateMax(hNemesys1, &MaxFlow);
	BOOST_CHECK_EQUAL(ERR_NOERR, Result);

	Result = LCP_PumpVolume(hNemesys1, 0 - MaxVolume, MaxFlow);
    BOOST_CHECK_EQUAL(ERR_NOERR, Result);
    bool PumpingFinished = waitDosageFinished(hNemesys1, 10);
	BOOST_CHECK(PumpingFinished);

	Result = LCP_PumpVolume(hNemesys1, MaxVolume, MaxFlow);
    BOOST_CHECK_EQUAL(ERR_NOERR, Result);
    PumpingFinished = waitDosageFinished(hNemesys1, 10);
	BOOST_CHECK(PumpingFinished);
}


//============================================================================
// Test if generation of constant flow works properly
//============================================================================
BOOST_AUTO_TEST_CASE(testGenerateFlow)
{
	double MaxFlow;
	LCP_GetFlowRateMax(hNemesys1, &MaxFlow);
	BOOST_CHECK_EQUAL(ERR_NOERR, Result);

	Result = LCP_GenerateFlow(hNemesys1, MaxFlow);
    BOOST_CHECK_EQUAL(ERR_NOERR, Result);
    CThread::sleep(1000);

    double FlowIs;
    Result = LCP_GetFlowIs(hNemesys1, &FlowIs);
    BOOST_CHECK_EQUAL(ERR_NOERR, Result);
    BOOST_CHECK_CLOSE(MaxFlow, FlowIs, 0.01);

    bool PumpingFinished = waitDosageFinished(hNemesys1, 30);
	BOOST_CHECK(PumpingFinished);
}


//============================================================================
// Checks if setting a certain syringe level works fine
//============================================================================
BOOST_AUTO_TEST_CASE(testSetSyringeLevel)
{
	double MaxFlow;
	double MaxVolume;

	LCP_GetFlowRateMax(hNemesys1, &MaxFlow);
	BOOST_CHECK_EQUAL(ERR_NOERR, Result);
	MaxFlow /= 2;

	Result = LCP_GetVolumeMax(hNemesys1, &MaxVolume);
	BOOST_CHECK_EQUAL(ERR_NOERR, Result);
	MaxVolume /= 2;

	Result = LCP_SetFillLevel(hNemesys1, MaxVolume, MaxFlow);
    BOOST_CHECK_EQUAL(ERR_NOERR, Result);
    bool PumpingFinished = waitDosageFinished(hNemesys1, 30);
	BOOST_CHECK(PumpingFinished);

	double FillLevelIs;
	Result = LCP_GetFillLevel(hNemesys1, &FillLevelIs);
    BOOST_CHECK_EQUAL(ERR_NOERR, Result);
    BOOST_CHECK_CLOSE(MaxVolume, FillLevelIs, 0.01);

	Result = LCP_SetFillLevel(hNemesys1, 0, MaxFlow);
    BOOST_CHECK_EQUAL(ERR_NOERR, Result);
    PumpingFinished = waitDosageFinished(hNemesys1, 30);
	BOOST_CHECK(PumpingFinished);

	Result = LCP_GetFillLevel(hNemesys1, &FillLevelIs);
    BOOST_CHECK_EQUAL(ERR_NOERR, Result);
    BOOST_CHECK_CLOSE(0, FillLevelIs, 0.01);
}


//============================================================================
// Checks neMESYS valve switching
//============================================================================
BOOST_AUTO_TEST_CASE(testValve)
{
	long HasValve = LCP_HasValve(hNemesys1);
	BOOST_CHECK_GE(HasValve, 0);

	if (!HasValve)
	{
		BOOST_TEST_MESSAGE("no valve installed");
		return;
	}

	dev_hdl hValve1;
	Result = LCP_GetValveHandle(hNemesys1, &hValve1);
	BOOST_CHECK_GT(hValve1, 0);
	BOOST_CHECK_EQUAL(ERR_NOERR, Result);

	long NumberOfValvePositions = LCV_NumberOfValvePositions(hValve1);
    BOOST_CHECK_GT(NumberOfValvePositions, 0);
    BOOST_TEST_MESSAGE("Valve positions: " << NumberOfValvePositions);

    for (int i = 0; i < NumberOfValvePositions; ++i)
    {
    	Result = LCV_SwitchValveToPosition(hValve1, i);
    	BOOST_CHECK_EQUAL(Result, ERR_NOERR);
    	CThread::sleep(200); // give valve some time to move to target
    	Result = LCV_ActualValvePosition(hValve1);
    	BOOST_CHECK_EQUAL(Result, i);
    }
}

//============================================================================
// Checks if aspiration works properly
//============================================================================
BOOST_AUTO_TEST_CASE(stressTestManyInstructions)
{
	double MaxVolume;
	double MaxFlow;

	// Ensure that syringe is fully drawn up

	Result = LCP_GetVolumeMax(hNemesys1, &MaxVolume);
	BOOST_CHECK_EQUAL(ERR_NOERR, Result);

	Result = LCP_GetFlowRateMax(hNemesys1, &MaxFlow);
	BOOST_CHECK_EQUAL(ERR_NOERR, Result);
	Result = LCP_SetFillLevel(hNemesys1, MaxVolume, MaxFlow);
	BOOST_CHECK_EQUAL(ERR_NOERR, Result);

    bool PumpingFinished = waitDosageFinished(hNemesys1, 30);
	BOOST_CHECK(PumpingFinished);

	const double Pi = atan(1) * 4;
	double T_ms = 20000;
	double t_ms = 0;
	double t_sample_ms = 100;
	double Flow = 0;
	std::vector<double> TimeValues;
	std::chrono::time_point<std::chrono::system_clock> StartVelocityProfile,
		FinishVelocityProfile, StartMove, StopMove;

	StartVelocityProfile = std::chrono::system_clock::now();

	//
	// Creates a half sinus wave flow rate profile
	//
	for(t_ms = 0; t_ms <= T_ms / 2; t_ms += t_sample_ms)
	{
		Flow = MaxFlow / 2 * sin(t_ms * 2 * Pi / T_ms);
		StartMove = std::chrono::system_clock::now();
		Result = LCP_GenerateFlow(hNemesys1, Flow);
		StopMove = std::chrono::system_clock::now();
	    std::chrono::duration<double> elapsed_seconds = StopMove - StartMove;
	    TimeValues.push_back(elapsed_seconds.count());

		if(Result != ERR_NOERR)
		{
			break;
		}
		CThread::sleep(t_sample_ms);
	}
	FinishVelocityProfile = std::chrono::system_clock::now();
    BOOST_CHECK_EQUAL(ERR_NOERR, Result);

    // Prints duration of each single move.
    int i = 0;
    for(double Duration : TimeValues)
    {
    	BOOST_TEST_MESSAGE("Duration Move " << i << ": " << Duration << "s");
    	i++;
    }

    // Prints duration for generating sinus wave velocity profile
    std::chrono::duration<double> elapsed_seconds = FinishVelocityProfile-StartVelocityProfile;
    BOOST_TEST_MESSAGE("Elapsed time: " << elapsed_seconds.count() << "s.");
}

//============================================================================
// waits until axis finished positioning (with timeout)
//============================================================================
bool waitAxisTargetReached(dev_hdl hAxis, uint32_t TimeoutSeconds)
{
	CPollingTimer Timer(TimeoutSeconds * 1000);
	do
	{
		CThread::sleep(100);
		Result = LCA_IsAxisTargetPosReached(hAxis);
	}
	while ((0 == Result) && !Timer.isExpired());

	return (Result > 0);
}

//============================================================================
// Tests positioning of neMESYS axis
//============================================================================
BOOST_AUTO_TEST_CASE(testNemesysAxisPositioning)
{
	hNemesys1Axis = LCP_GetPumpDriveHandle(hNemesys1);
	BOOST_CHECK_GT(hNemesys1Axis, 0);

	double MaxVelocity;
	Result = LCA_GetAxisVelMax(hNemesys1Axis, &MaxVelocity);
	BOOST_CHECK_EQUAL(Result, ERR_NOERR);

	double MinPosition;
	Result = LCA_GetAxisPosMin(hNemesys1Axis, &MinPosition);
	BOOST_CHECK_EQUAL(Result, ERR_NOERR);
	BOOST_TEST_MESSAGE("Min Position: " << MinPosition);

	Result = LCA_MoveToPos(hNemesys1Axis, MinPosition, MaxVelocity, 0);
	BOOST_CHECK_EQUAL(Result, ERR_NOERR);

	bool Result = waitAxisTargetReached(hNemesys1Axis, 30);
	BOOST_CHECK_EQUAL(Result, true);

	double MaxPositon;
	Result = LCA_GetAxisPosMax(hNemesys1Axis, &MaxPositon);
	BOOST_CHECK_EQUAL(Result, ERR_NOERR);

	Result = LCA_MoveToPos(hNemesys1Axis, MaxPositon, MaxVelocity, 0);
	BOOST_CHECK_EQUAL(Result, ERR_NOERR);
	Result = waitAxisTargetReached(hNemesys1Axis, 30);
	BOOST_CHECK_EQUAL(Result, true);
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
// EOF capi_test.cpp
