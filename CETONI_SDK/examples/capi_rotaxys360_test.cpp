//============================================================================
/// \file   capi_test.cpp
/// \author Uwe Kindler
/// \date   24.11.2009
/// \brief  Test of labbCAN C-API
//============================================================================


//============================================================================
//                                   INCLUDES
//============================================================================
#include <boost/math/constants/constants.hpp>

// We neeed to fix labbCAN_MotionControl_API.h because the defines colide with
// the unit types include by the Rotaxys360 header
#include <labbcan/driver/canopen/AxisSystem/Rotaxys360.h>
#include <labbcan/c_api/labbCAN_Bus_API.h>
#include <labbcan/c_api/labbCAN_MotionControl_API.h>

#include <labbcan/common/Point.h>
#include <labbcan/common/PolarPoint.h>
#include <labbcan/common/labbcan_test_helpers.h>


#include <usl/core/Thread.h>
#include <usl/core/PollingTimer.h>
#include <log4cplus/logger.h>
#include <diag/diag.h>


using namespace Lcl;
using namespace Usl;
using namespace boost;
#define BOOST_TEST_MODULE capi_rotaxys_test
#include <boost/test/unit_test.hpp>


//============================================================================
//                                DATA TYPES
//============================================================================



//============================================================================
//                               GLOBAL DATA
//============================================================================
dev_hdl hAxisX;
dev_hdl hAxis;
dev_hdl hAxisSystem;
long Result;
const char* const Device1Name = "rotAXYS360_1";
Lcl::CRotaxys360* rotAXYS;


//============================================================================
// Initialize C-API - open bus library
//============================================================================
BOOST_AUTO_TEST_CASE(testCapiOpen)
{
    Result = LCB_Open("config/testconfig_qmixsdk", 0);
    BOOST_REQUIRE_EQUAL(ERR_NOERR, Result);
}


//============================================================================
// Lookup for axis devices and axis system devices
//============================================================================
BOOST_AUTO_TEST_CASE(testDeviceNameLookup)
{
    Result = LCA_LookupAxisByName("rotAXYS360_1_Lift", &hAxisX);
    BOOST_CHECK_GT(hAxisX, 0);
    CHECK_RETURN_CODE(Result);

    Result = LCA_LookupAxisSystemByName(Device1Name, &hAxisSystem);
    BOOST_CHECK_GT(hAxisSystem, 0);
    CHECK_RETURN_CODE(Result);

    long AxisSystemCount = LCA_GetNoOfAxisSystems();
    BOOST_CHECK_GT(AxisSystemCount, 0);
    long i;
    dev_hdl hAxisSystem2;
    for (i = 0; i < AxisSystemCount; ++i)
    {
    	Result = LCA_GetAxisSystemHandle(i, &hAxisSystem2);
    	if (Result != ERR_NOERR)
    	{
    		continue;
    	}

    	if (hAxisSystem == hAxisSystem2)
    	{
    		break;
    	}
    }

    BOOST_CHECK_LT(i, AxisSystemCount);

    dev_hdl hAxis;
    Result = LCA_GetAxisHandle(hAxisSystem, 2, &hAxis);
    BOOST_CHECK_EQUAL(hAxisX, hAxis);
    CHECK_RETURN_CODE(Result);

    rotAXYS = dynamic_cast<Lcl::CRotaxys360*>(CRotaxys360::NameServer.getObject(Device1Name));
    BOOST_CHECK(rotAXYS != nullptr);
}


//============================================================================
// Startup labbCAN bus communication
//============================================================================
BOOST_AUTO_TEST_CASE(testBusStart)
{
	Result = LCB_Start();
    BOOST_CHECK_EQUAL(Result, ERR_NOERR);
    Result = LCB_Log("C-API Log Test Message");
    BOOST_CHECK_EQUAL(Result, ERR_NOERR);
}


//============================================================================
// waits until axis finished homing move (with timeout)
//============================================================================
bool waitAxisHomingAttained(dev_hdl hAxis, uint32_t TimeoutSeconds)
{
	CPollingTimer Timer(TimeoutSeconds * 1000);
	do
	{
		CThread::sleep(100);
		Result = LCA_IsAxisHomingPosAttained(hAxis);
	}
	while ((0 == Result) && !Timer.isExpired());

	return (Result > 0);
}


//============================================================================
// waits until axis system finished homing move (with timeout)
//============================================================================
bool waitHomingAttained(dev_hdl AxisSystem, uint32_t TimeoutSeconds)
{
	CPollingTimer Timer(TimeoutSeconds * 1000);
	do
	{
		CThread::sleep(100);
		Result = LCA_IsHomingPosAttained(AxisSystem);
	}
	while ((0 == Result) && !Timer.isExpired());

	return (Result > 0);
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
// waits until axis system finished positioning (with timeout)
//============================================================================
bool waitTargetReached(dev_hdl AxisSystem, uint32_t TimeoutSeconds)
{
	CPollingTimer Timer(TimeoutSeconds * 1000);
	do
	{
		CThread::sleep(100);
		Result = LCA_IsTargetPosReached(AxisSystem);
	}
	while ((0 == Result) && !Timer.isExpired());

	return (Result > 0);
}


//============================================================================
// Tests enabling of axis system
//============================================================================
BOOST_AUTO_TEST_CASE(testAxisSystemEnable)
{
	Result = LCA_Enable(hAxisSystem);
    BOOST_CHECK_EQUAL(Result, ERR_NOERR);
    for (int i = 0; i < 3; ++i)
    {
    	dev_hdl Axis;
    	Result = LCA_GetAxisHandle(hAxisSystem, i, &Axis);
    	CHECK_RETURN_CODE(Result);
    	Result = LCA_IsAxisEnabled(Axis);
    	BOOST_CHECK_GT(Result, 0);
    }
}


//============================================================================
// Tests axis system homing
//============================================================================
BOOST_AUTO_TEST_CASE(testAxisSystemHoming)
{
	Result = LCA_FindHome(hAxisSystem);
	bool HomingAttained = waitHomingAttained(hAxisSystem, 20);
	BOOST_CHECK_EQUAL(HomingAttained, true);
	CThread::sleep(500); // let device send process data and reset position counter
}


//============================================================================
// Tests positioning
//============================================================================
BOOST_AUTO_TEST_CASE(testPositioning)
{
	static const int TESTPOINTS = 4;
	static const CPoint TestPosTbl[TESTPOINTS] =
	{
		 CPoint(-49.51, -121.49),
		 CPoint( 49.26, -121.49),
		 CPoint(-49.51,  -58.50),
		 CPoint( 49.26,  -58.50),
	};

	for (int i = 0; i < TESTPOINTS; ++i)
	{
		const CPoint* Point = &TestPosTbl[i];
		Result = LCA_MoveToPosXY(hAxisSystem, Point->x(), Point->y(), 1, 0);
		BOOST_CHECK_EQUAL(ERR_NOERR, Result);
		bool TargetReached = waitTargetReached(hAxisSystem, 5);
		BOOST_CHECK_EQUAL(TargetReached, true);

		dev_hdl ZAxis;
		Result = LCA_GetAxisHandle(hAxisSystem, 2, &ZAxis);
		CHECK_RETURN_CODE(Result);

		double MinZ;
		Result = LCA_GetAxisPosMin(ZAxis, &MinZ);
		BOOST_CHECK_EQUAL(ERR_NOERR, Result);
		Result = LCA_MoveToPos(ZAxis, MinZ, LCA_MAX_VELOCITY, 0);
		BOOST_CHECK_EQUAL(ERR_NOERR, Result);
		TargetReached = waitAxisTargetReached(ZAxis, 5);
		BOOST_CHECK_EQUAL(TargetReached, true);

		double MaxZ;
		Result = LCA_GetAxisPosMax(ZAxis, &MaxZ);
		BOOST_CHECK_EQUAL(ERR_NOERR, Result);
		Result = LCA_MoveToPos(ZAxis, MaxZ, LCA_MAX_VELOCITY, 0);
		BOOST_CHECK_EQUAL(ERR_NOERR, Result);
		TargetReached = waitAxisTargetReached(ZAxis, 5);
		BOOST_CHECK_EQUAL(TargetReached, true);
	}
}


//============================================================================
// Execute some rotations in both directions at a certain radius position
//============================================================================
void testRotationOnRadius(double Radius, double DistanceDegree, int Iterations)
{
	CPolarPoint PolarPoint(0, Radius);
	CPoint TargetXY = rotAXYS->toCartesianPoint(PolarPoint);
	Result = LCA_MoveToPosXY(hAxisSystem, TargetXY.x(), TargetXY.y(), 1, 0);
	BOOST_CHECK_EQUAL(ERR_NOERR, Result);
	bool TargetReached = waitTargetReached(hAxisSystem, 3);
	BOOST_CHECK_EQUAL(TargetReached, true);

	bool LoopSuccess = false;
	for (int i = 0; i < Iterations; ++i)
	{
		LoopSuccess = false;
		PolarPoint.setAzimuth(PolarPoint.azimuth() + CPolarPoint::degreeToRadians(DistanceDegree));
		TargetXY = rotAXYS->toCartesianPoint(PolarPoint);
		Result = LCA_MoveToPosXY(hAxisSystem, TargetXY.x(), TargetXY.y(), 1, 0);
		BREAK_ON_ERROR(Result);
		bool TargetReached = waitTargetReached(hAxisSystem, 3);
		if (!TargetReached)
		{
			break;
		}
		LoopSuccess = true;
	}
	BOOST_CHECK_EQUAL(LoopSuccess, true);

	for (int i = 0; i < Iterations; ++i)
	{
		LoopSuccess = false;
		PolarPoint.setAzimuth(PolarPoint.azimuth() - CPolarPoint::degreeToRadians(DistanceDegree));
		TargetXY = rotAXYS->toCartesianPoint(PolarPoint);
		Result = LCA_MoveToPosXY(hAxisSystem, TargetXY.x(), TargetXY.y(), 1, 0);
		BREAK_ON_ERROR(Result);
		bool TargetReached = waitTargetReached(hAxisSystem, 3);
		if (!TargetReached)
		{
			break;
		}
		LoopSuccess = true;
	}
	BOOST_CHECK_EQUAL(LoopSuccess, true);
}


//============================================================================
// Tests positioning on outer maximum radius
//============================================================================
BOOST_AUTO_TEST_CASE(testRotationMaxRadius)
{
	double MaxRadius;
	dev_hdl RadiusAxis;
	Result = LCA_GetAxisHandle(hAxisSystem, CRotaxys360::AXIS_RADIUS, &RadiusAxis);
	CHECK_RETURN_CODE(Result);

	Result = LCA_GetAxisPosMax(RadiusAxis, &MaxRadius);
	BOOST_CHECK_EQUAL(ERR_NOERR, Result);
	testRotationOnRadius(MaxRadius, 170, 6);
	testRotationOnRadius(MaxRadius, 1, 30);
}


//============================================================================
// Tests positioning on inner minimum radius
//============================================================================
BOOST_AUTO_TEST_CASE(testRotationMinRadius)
{
	double MinRadius;
	dev_hdl RadiusAxis;
	Result = LCA_GetAxisHandle(hAxisSystem, CRotaxys360::AXIS_RADIUS, &RadiusAxis);
	CHECK_RETURN_CODE(Result);

	Result = LCA_GetAxisPosMin(RadiusAxis, &MinRadius);
	BOOST_CHECK_EQUAL(ERR_NOERR, Result);
	testRotationOnRadius(MinRadius, 170, 6);
	testRotationOnRadius(MinRadius, 1, 30);
}


//============================================================================
// Test stop functionality
// The rotAXYS axis system uses timers internally to trigger delay of the
// radius axis movement. This test ensures, that the timers are properly
// stopped if stop has been called
//============================================================================
BOOST_AUTO_TEST_CASE(testStop)
{
	double MaxRadius;
	dev_hdl RadiusAxis;
	Result = LCA_GetAxisHandle(hAxisSystem, CRotaxys360::AXIS_RADIUS, &RadiusAxis);
	CHECK_RETURN_CODE(Result);

	Result = LCA_GetAxisPosMax(RadiusAxis, &MaxRadius);
	CPolarPoint PolarPoint(0, MaxRadius);
	CPoint TargetXY = rotAXYS->toCartesianPoint(PolarPoint);
	Result = LCA_MoveToPosXY(hAxisSystem, TargetXY.x(), TargetXY.y(), 1, 0);
	BOOST_CHECK_EQUAL(ERR_NOERR, Result);
	bool TargetReached = waitTargetReached(hAxisSystem, 3);
	BOOST_CHECK_EQUAL(TargetReached, true);
	PolarPoint.setAzimuth(PolarPoint.azimuth() - CPolarPoint::degreeToRadians(170));
	TargetXY = rotAXYS->toCartesianPoint(PolarPoint);

	double Radius1;
	Result = LCA_GetAxisPosIs(RadiusAxis, &Radius1);
	BOOST_CHECK_EQUAL(ERR_NOERR, Result);
	for (int i = 0; i < 5; ++i)
	{
		Result = LCA_MoveToPosXY(hAxisSystem, TargetXY.x(), TargetXY.y(), 1, 0);
		BOOST_CHECK_EQUAL(ERR_NOERR, Result);
		Result = LCA_StopMove(hAxisSystem);
		CThread::sleep(700);
	}
	double Radius2;
	Result = LCA_GetAxisPosIs(RadiusAxis, &Radius2);
	BOOST_CHECK_EQUAL(ERR_NOERR, Result);

	long Simulated = LCB_IsSimulated(RadiusAxis);
	CHECK_RETURN_CODE(Simulated);

	if (Simulated)
	{
		BOOST_CHECK_CLOSE(Radius1, Radius2, 1.2);
	}
	else
	{
		BOOST_CHECK_CLOSE(Radius1, Radius2, 0.0000001);
	}
}


//============================================================================
// Tests if disabling of axes works properly
//============================================================================
BOOST_AUTO_TEST_CASE(testAxesDisable)
{
	Result = LCA_Disable(hAxisSystem);
	BOOST_CHECK_EQUAL(ERR_NOERR, Result);

	CThread::sleep(200);///< give device some time to go into disabled state
	long AxisCount = LCA_GetAxisSystemAxisNumber(hAxisSystem);
	BOOST_CHECK_GT(AxisCount, 0);

	for (int i = 0; i < AxisCount; ++i)
	{
		dev_hdl Axis;
		Result = LCA_GetAxisHandle(hAxisSystem, i, &Axis);
		CHECK_RETURN_CODE(Result);

		BOOST_CHECK_GT(Axis, 0);
		Result = LCA_IsAxisEnabled(Axis);
		BOOST_CHECK_EQUAL(0, Result);
		Result = LCA_IsAxisInFaultState(Axis);
		BOOST_CHECK_EQUAL(0, Result);
	}
}


//============================================================================
// Tests if C-API shutdown works properly
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
