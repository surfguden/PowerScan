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

#include <labbcan/c_api/labbCAN_Bus_API.h>
#include <labbcan/c_api/labbCAN_MotionControl_API.h>
#include <labbcan/common/Point.h>
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

static const int TESTPOINTS = 4;
static const CPoint TestPosTbl[TESTPOINTS] =
{
	 CPoint(-49.51, -121.49),
	 CPoint( 49.26, -121.49),
	 CPoint(-49.51,  -58.50),
	 CPoint( 49.26,  -58.50),
};


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
    Result = LCA_LookupAxisByName("rotAXYS_1_Lift", &hAxisX);
    BOOST_CHECK_GT(hAxisX, 0);
    CHECK_RETURN_CODE(Result);

    Result = LCA_LookupAxisSystemByName("rotAXYS_1", &hAxisSystem);
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
	bool HomingAttained = waitHomingAttained(hAxisSystem, 10);
	BOOST_CHECK_EQUAL(HomingAttained, true);
}


//============================================================================
// Tests coordinate conversion
//============================================================================
BOOST_AUTO_TEST_CASE(testCoordinateConversion)
{
	double PosX;
	double PosY;
	Result = LCA_GetActualPostitionXY(hAxisSystem, &PosX, &PosY);
	BOOST_CHECK_EQUAL(ERR_NOERR, Result);
	BOOST_TEST_MESSAGE("PosX: " << PosX << "  PosY: " << PosY);

	dev_hdl RotationAxis;
	Result = LCA_GetAxisHandle(hAxisSystem, 0, &RotationAxis);
	BOOST_CHECK_NE(0, RotationAxis);
	CHECK_RETURN_CODE(Result);

	dev_hdl RadiusAxis;
	Result = LCA_GetAxisHandle(hAxisSystem, 1, &RadiusAxis);
	BOOST_CHECK_NE(0, RadiusAxis);
	CHECK_RETURN_CODE(Result);

	double Radius;
	double Azimuth;
	Result = LCA_GetAxisPosIs(RotationAxis, &Azimuth);
	BOOST_CHECK_EQUAL(ERR_NOERR, Result);
	Result = LCA_GetAxisPosIs(RadiusAxis, &Radius);
	BOOST_CHECK_EQUAL(ERR_NOERR, Result);
	BOOST_TEST_MESSAGE("Azimuth: " << Azimuth << "  Radius: " << Radius);

	double JibLength = -18;
	double d1 = sqrt(pow(Radius, 2) + pow(JibLength, 2));
	double beta = math::constants::pi<double>() / 2 - Azimuth
		- atan2(JibLength , Radius);
	double x = d1 * sin(beta);
	double y = d1 * cos(beta);
	BOOST_TEST_MESSAGE("X: " << x << "  Y: " << y);
	BOOST_CHECK_CLOSE(PosX, x, 0.0001);
	BOOST_CHECK_CLOSE(PosY, y, 0.0001);
}


//============================================================================
// Tests positioning
//============================================================================
BOOST_AUTO_TEST_CASE(testPositioning)
{
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

		Result = LCA_MoveToPos(ZAxis, 0, LCA_MAX_VELOCITY, 0);
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
// Tests positioning with lower speed
//============================================================================
BOOST_AUTO_TEST_CASE(testPositioningSlow)
{
	static const double SLOW_SPEED = 0.3;

	for (int i = 0; i < TESTPOINTS; ++i)
	{
		const CPoint* Point = &TestPosTbl[i];
		Result = LCA_MoveToPosXY(hAxisSystem, Point->x(), Point->y(), SLOW_SPEED, 0);
		BOOST_CHECK_EQUAL(ERR_NOERR, Result);
		bool TargetReached = waitTargetReached(hAxisSystem, 5);
		BOOST_CHECK_EQUAL(TargetReached, true);

		dev_hdl ZAxis;
		Result = LCA_GetAxisHandle(hAxisSystem, 2, &ZAxis);
		CHECK_RETURN_CODE(Result);

		Result = LCA_MoveToPos(ZAxis, 0, LCA_MAX_VELOCITY, 0);
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
// Tests the safe positioning feature
//============================================================================
BOOST_AUTO_TEST_CASE(testSafePositioning)
{
	dev_hdl ZAxis;
	Result = LCA_GetAxisHandle(hAxisSystem, 2, &ZAxis);
	CHECK_RETURN_CODE(Result);

	Result = LCB_IsSimulated(ZAxis);
	REQUIRE_ERR_NOERR(Result);
	if (Result > 0)
	{
		BOOST_TEST_MESSAGE("Skipping testSafePositioning because it is not supported by simulated devices");
		return;
	}

	Result = LCB_SetDeviceProperty(hAxisSystem, RotaxysPropertySafeRotation, 0);
	CHECK_RETURN_CODE(Result);


	// Move to lower limit and check if upper limit sensor is off
	Result = LCA_MoveToPos(ZAxis, 0, LCA_MAX_VELOCITY, 0);
	CHECK_RETURN_CODE(Result);
	bool TargetReached = waitAxisTargetReached(ZAxis, 5);
	BOOST_CHECK_EQUAL(TargetReached, true);
	double SensorState;
	Result = LCB_GetDeviceProperty(hAxisSystem,
		RotaxysPropertyUpperLimitSensorState, &SensorState);
	CHECK_RETURN_CODE(Result);
	BOOST_REQUIRE_NE(SensorState, 1);

	// movement should be possible because safe rotation is off
	const CPoint* Point = &TestPosTbl[0];
	Result = LCA_MoveToPosXY(hAxisSystem, Point->x(), Point->y(), 1, 0);
	CHECK_RETURN_CODE(Result);
	TargetReached = waitTargetReached(hAxisSystem, 5);
	BOOST_CHECK_EQUAL(TargetReached, true);

	Result = LCB_SetDeviceProperty(hAxisSystem, RotaxysPropertySafeRotation, 1);
	CHECK_RETURN_CODE(Result);

	// Movement should be blocked because safe rotation is on and upper sensor
	// is off
	Point = &TestPosTbl[1];
	Result = LCA_MoveToPosXY(hAxisSystem, Point->x(), Point->y(), 1, 0);
	BOOST_CHECK_EQUAL(Result, -ERR_PERM);


	// move to upper limit and check if upper limit sensor is on
	double MaxZ;
	Result = LCA_GetAxisPosMax(ZAxis, &MaxZ);
	BOOST_CHECK_EQUAL(ERR_NOERR, Result);
	Result = LCA_MoveToPos(ZAxis, MaxZ, LCA_MAX_VELOCITY, 0);
	BOOST_CHECK_EQUAL(ERR_NOERR, Result);
	TargetReached = waitAxisTargetReached(ZAxis, 5);
	BOOST_CHECK_EQUAL(TargetReached, true);
	Result = LCB_GetDeviceProperty(hAxisSystem,
		RotaxysPropertyUpperLimitSensorState, &SensorState);
	CHECK_RETURN_CODE(Result);
	BOOST_CHECK_EQUAL(SensorState, 1);

	// movement should be possible because lift axis is in its top most position
	Result = LCA_MoveToPosXY(hAxisSystem, Point->x(), Point->y(), 1, 0);
	CHECK_RETURN_CODE(Result);
	TargetReached = waitTargetReached(hAxisSystem, 5);
	BOOST_CHECK_EQUAL(TargetReached, true);

	Result = LCB_SetDeviceProperty(hAxisSystem, RotaxysPropertySafeRotation, 0);
	CHECK_RETURN_CODE(Result);
}


//============================================================================
// Tests if disabling of axes works properly
//============================================================================
BOOST_AUTO_TEST_CASE(testAxesDisable)
{
	Result = LCA_Disable(hAxisSystem);
	BOOST_CHECK_EQUAL(ERR_NOERR, Result);

	CThread::sleep(200);///< give device some time to gointo disabled state
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
