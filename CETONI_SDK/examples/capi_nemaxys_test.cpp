//============================================================================
/// \file   capi_test.cpp
/// \author Uwe Kindler
/// \date   24.11.2009
/// \brief  Test of labbCAN C-API
//============================================================================


//============================================================================
//                                   INCLUDES
//============================================================================
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
#define BOOST_TEST_MODULE capi_nemaxys_test
#include <boost/test/unit_test.hpp>


//============================================================================
//                                DATA TYPES
//============================================================================



//============================================================================
//                               GLOBAL DATA
//============================================================================
dev_hdl hAxisX = 0;
dev_hdl hAxis = 0;
dev_hdl hAxisSystem = 0;
long Result = 0;


//============================================================================
// Initialize C-API - open bus library
//============================================================================
BOOST_AUTO_TEST_CASE(testCapiOpen)
{
    using namespace boost::unit_test;
    //framework::master_test_suite().argv[1];
    Result = LCB_Open("config/testconfig_qmixsdk", 0);
    CHECK_RETURN_CODE(Result);
    Result = LCB_Close();
    CHECK_RETURN_CODE(Result);
    Result = LCB_Open("config/testconfig_qmixsdk", 0);
    CHECK_RETURN_CODE(Result);
    Result = LCB_Close();
    CHECK_RETURN_CODE(Result);
    Result = LCB_Open("config/testconfig_qmixsdk", 0);
    REQUIRE_ERR_NOERR(Result);
}


//============================================================================
// Lookup for axis devices and axis system devices
//============================================================================
BOOST_AUTO_TEST_CASE(testDeviceNameLookup)
{
    Result = LCA_LookupAxisByName("neMAXYS1_X", &hAxisX);
    BOOST_CHECK_NE(hAxisX, 0);
    CHECK_RETURN_CODE(Result);

    Result = LCA_LookupAxisSystemByName("neMAXYS1", &hAxisSystem);
    BOOST_CHECK_NE(hAxisSystem, 0);
    CHECK_RETURN_CODE(Result);

    char Name[64];
    Result = LCB_GetDevName(hAxisSystem, Name, sizeof(Name));
    CHECK_RETURN_CODE(Result);

    dev_hdl hAxisSystem2;
    Result = LCA_GetAxisSystemHandle(0, &hAxisSystem2);
    BOOST_CHECK_EQUAL(hAxisSystem, hAxisSystem2);
    CHECK_RETURN_CODE(Result);

    dev_hdl hAxis1;
    Result = LCA_GetAxisHandle(hAxisSystem, 0, &hAxis1);
    BOOST_CHECK_EQUAL(hAxisX, hAxis1);
    CHECK_RETURN_CODE(Result);

    Result = LCB_GetDevName(hAxis1, Name, sizeof(Name));
    CHECK_RETURN_CODE(Result);

    dev_hdl hAxis2;
    Result = LCA_LookupAxisByName("invalid axis name", &hAxis2);
    BOOST_CHECK_BITWISE_EQUAL(hAxis2, (dev_hdl)0);
    BOOST_CHECK_EQUAL(Result, -ERR_NODEV);
}


//============================================================================
// Test device info functions
//============================================================================
BOOST_AUTO_TEST_CASE(testDeviceInfo)
{
	char StringBuf[64];
	Result = LCB_GetDevName(hAxisSystem, StringBuf, sizeof(StringBuf));
	BOOST_TEST_MESSAGE("Device name: " << StringBuf);
}


//============================================================================
// Startup labbCAN bus communication
//============================================================================
BOOST_AUTO_TEST_CASE(testBusStart)
{
	Result = LCB_Start();
    CHECK_RETURN_CODE(Result);
    Result = LCB_Log("C-API Log Test Message");
    CHECK_RETURN_CODE(Result);
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
    CHECK_RETURN_CODE(Result);
    for (int i = 0; i < 3; ++i)
    {
    	dev_hdl Axis;
    	Result = LCA_GetAxisHandle(hAxisSystem, i, &Axis);
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
	bool HomingAttained = waitHomingAttained(hAxisSystem, 30);
	BOOST_CHECK_EQUAL(HomingAttained, true);
}


//============================================================================
// Tests positioning in XY space
//============================================================================
BOOST_AUTO_TEST_CASE(testXyPositioning)
{
	dev_hdl AxisX;
	Result = LCA_GetAxisHandle(hAxisSystem, 0, &AxisX);
	BOOST_CHECK_GT(AxisX, 0);
	CHECK_RETURN_CODE(Result);

	dev_hdl AxisY;
	Result = LCA_GetAxisHandle(hAxisSystem, 1, &AxisY);
	BOOST_CHECK_GT(AxisY, 0);
	CHECK_RETURN_CODE(Result);

	double maxX;
	double maxY;

	long Result = LCA_GetAxisPosMax(AxisX, &maxX);
	Result = LCA_GetAxisPosMax(AxisY, &maxY);
	CHECK_RETURN_CODE(Result);

	std::vector<CPoint> Targets;
	Targets.push_back(CPoint(maxX, maxY));
	Targets.push_back(CPoint(0,    0));

	for (unsigned int i = 0; i < Targets.size(); ++i)
	{
		CPoint TargetPosition = Targets.at(i);
		Result = LCA_MoveToPosXY(hAxisSystem, TargetPosition.x(),
			TargetPosition.y(), 1, 0);
		CHECK_RETURN_CODE(Result);
		bool Result = waitTargetReached(hAxisSystem, 10);
		BOOST_CHECK_EQUAL(Result, true);
	}

	for (unsigned int i = 0; i < Targets.size(); ++i)
	{
		CPoint TargetPosition = Targets.at(i);
		Result = LCA_MoveToPosXY(hAxisSystem, TargetPosition.x(),
			TargetPosition.y(), 0.5, 0);
		CHECK_RETURN_CODE(Result);
		bool Result = waitTargetReached(hAxisSystem, 30);
		BOOST_CHECK_EQUAL(Result, true);
	}
}


//============================================================================
// Tests positioning of Z axis
//============================================================================
BOOST_AUTO_TEST_CASE(testZPositioning)
{
	dev_hdl AxisZ;
	Result = LCA_GetAxisHandle(hAxisSystem, 2, &AxisZ);
	BOOST_CHECK_GT(AxisZ, 0);
	CHECK_RETURN_CODE(Result);

	double MaxVelocity;
	Result = LCA_GetAxisVelMax(AxisZ, &MaxVelocity);
	CHECK_RETURN_CODE(Result);

	double MinPosition;
	Result = LCA_GetAxisPosMin(AxisZ, &MinPosition);
	CHECK_RETURN_CODE(Result);
	Result = LCA_MoveToPos(AxisZ, MinPosition, MaxVelocity, 0);
	CHECK_RETURN_CODE(Result);
	bool TargetReached = waitAxisTargetReached(AxisZ, 30);
	BOOST_CHECK_EQUAL(TargetReached, true);

	double MaxPositon;
	Result = LCA_GetAxisPosMax(AxisZ, &MaxPositon);
	CHECK_RETURN_CODE(Result);

	Result = LCA_MoveToPos(AxisZ, MaxPositon, MaxVelocity, 0);
	CHECK_RETURN_CODE(Result);
	Result = waitAxisTargetReached(AxisZ, 30);
	BOOST_CHECK_EQUAL(Result, true);
}


//============================================================================
// Test travel range of single axis
//============================================================================
void testAxisMinMaxPositioning(int AxisId)
{
	dev_hdl Axis;
	Result = LCA_GetAxisHandle(hAxisSystem, AxisId, &Axis);
	BOOST_CHECK_GT(Axis, 0);
	CHECK_RETURN_CODE(Result);

	double MaxVelocity;
	Result = LCA_GetAxisVelMax(Axis, &MaxVelocity);
	CHECK_RETURN_CODE(Result);

	double MinPosition;
	Result = LCA_GetAxisPosMin(Axis, &MinPosition);
	CHECK_RETURN_CODE(Result);
	Result = LCA_MoveToPos(Axis, MinPosition, MaxVelocity, 0);
	CHECK_RETURN_CODE(Result);
	bool TargetReached = waitAxisTargetReached(Axis, 30);
	BOOST_CHECK_EQUAL(TargetReached, true);

	double MaxPositon;
	Result = LCA_GetAxisPosMax(Axis, &MaxPositon);
	CHECK_RETURN_CODE(Result);
	Result = LCA_MoveToPos(Axis, MaxPositon, MaxVelocity, 0);
	CHECK_RETURN_CODE(Result);
	Result = waitAxisTargetReached(Axis, 30);
	BOOST_CHECK_EQUAL(Result, true);
}


//============================================================================
// Tests positioning of Z axis
//============================================================================
BOOST_AUTO_TEST_CASE(testAllAxisTravelRange)
{
	int AxisCount = LCA_GetAxisSystemAxisNumber(hAxisSystem);
	BOOST_CHECK_GT(AxisCount, 0);

	for (int i = 0; i < AxisCount; ++i)
	{
		testAxisMinMaxPositioning(i);
	}
}


//============================================================================
// Tests if disabling of axes works properly
//============================================================================
BOOST_AUTO_TEST_CASE(testAxesDisable)
{
	Result = LCA_Disable(hAxisSystem);
	CHECK_RETURN_CODE(Result);

	CThread::sleep(200);///< give device some time to go into disabled state
	long AxisCount = LCA_GetAxisSystemAxisNumber(hAxisSystem);
	BOOST_CHECK_GT(AxisCount, 0);

	for (int i = 0; i < AxisCount; ++i)
	{
		dev_hdl Axis;
		Result = LCA_GetAxisHandle(hAxisSystem, i, &Axis);
		BOOST_CHECK_GT(Axis, 0);
		CHECK_RETURN_CODE(Result);

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
    CHECK_RETURN_CODE(Result);

    Result = LCB_Close();
    CHECK_RETURN_CODE(Result);
}


/// \endcond
//---------------------------------------------------------------------------
// EOF capi_test.cpp
