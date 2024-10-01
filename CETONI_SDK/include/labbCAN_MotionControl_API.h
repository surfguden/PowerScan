#ifndef labbCAN_MotionControl_APIH
#define labbCAN_MotionControl_APIH
//===========================================================================
// CETONI GmbH
// Gewerbegebiet Korbwiesen
// Wiesenring 6
// 07554 Korbussen
//
// (c) Copyright 2017, CETONI GmbH
//
// All rights reserved. Cetoni's source code is an unpublished work
// and the use of a copyright notice does not imply otherwise. This
// source code contains confidential, trade secret material of
// cetoni GmbH. Any attempt or participation in deciphering, decoding,
// reverse engineering or in any way altering the source code is
// strictly prohibited, unless the prior written consent cetoni GmbH
// is obtained.
//
/// \file     labbCAN_MotionControl_API.h
/// \author   Uwe Kindler (UK)
/// \date     2012/05/29
/// \brief    labbCAN Motion Control Application Programming Interface
//
//===========================================================================

/**
 * \page MotionControl Motion Control Library
 * \ifnot bootstrap
 *    \tableofcontents
 *    <img src="Slider_MotionControl_API_color.jpg" align="center" style="padding-right: 10px; width: 800px;">
 * \else
 *    \image html Slider_MotionControl_API_color.jpg
 * \endif
 * \section MoCtrl_Introduction Introduction
 * The motion control library offers functions and data structures to work
 * with multi axis positioning systems. The API of the motion control library
 * provides functions to work with
 * - Axis systems (devices that consists of a number of single axes) such as
 *   LCA_FindHome() or LCA_MoveToPosXY()
 * - and single axis devices such as LCA_FindHomeOfAxis() and LCA_MoveToPos()
 *
 * So depending on the requirements of your application, you can work with
 * the single axis interface or with the multi axis interface. For some devices
 * such as the rotAXYS axis system it is much easier to use the multi axis
 * interface for positioning in XY space. Because the rotAXYS axis system has
 * a rotation axis, some translations needs to take place to convert between
 * polar and Cartesian coordinates. If you work with the single axis devices,
 * you need to do these translations for yourself. If you work with the multi
 * axis interface (LCA_MoveToPosXY()), then the axis system handles all the
 * translation stuff internally.
 *
 * \see See \subpage MotionControl_Devices page for detailed informations about
 * specific motion control devices.
 *
 *
 * ---
 *
 * \section MoCtrl_Including Including
 * The way how you include the library functions in your own windows program,
 * depends on the compiler and on the programming language you use. In order to
 * access the motion control API, you have to include the library
 * **labbCAN_MotionControl_API.dll** to your programming environment. You have
 * to copy this file to the working directory of your system or to the
 * application directory that contains your application EXE file.
 * Use the calling convention \b LCA_CALL for this library. This convention
 * is managing how the parameters are put on the stack and who is responsible
 * to clean the stack after the function execution.
 *
 * The interface of the library, constant definitions and declarations of the
 * library functions, is defined in the header file
 * \link labbCAN_MotionControl_API.h interface/labbCAN_MotionControl_API.h \endlink
 *
 * ---
 *
 * \section MoCtrl_Init Initialization
 * \subsection MoCtrl_Step1 Step 1 - Retrieve device handle
 * To work with axis systems or single axis devices, you need valid device
 * handles. A device handle is simply an opaque pointer to the internal device
 * object created by the labbCAN environment. So the first thing you need do to
 * is obtaining a valid device handle.
 *
 * You can get a valid axis system handle with the functions
 * LCA_LookupAxisSystemByName() or LCA_GetAxisSystemHandle():
 * \code
 * lca_hdl AxisSystemHandle;
 * Result = LCA_LookupAxisSystemByName("neMAXYS1", &AxisSystemHandle);
 * lca_hdl AxisSystemHandle2;
 * Result = LCA_GetAxisSystemHandle(1, &AxisSystemHandle2);
 * \endcode
 * You can get a valid axis handle, if you obtain a certain axis from a given
 * axis system device and a given axis index:
 * \code
 * lca_hdl hAxisX;
 * Result = LCA_GetAxisHandle(hAxisSystem, 0, &hAxisX);
 * \endcode
 * or if you query the global object pool for a registered named axis object:
 * \code
 * lca_hdl hNemaxysY;
 * Result = LCA_LookupAxisByName("neMAXYS1_Y", &hNemaxysY);
 * lca_hdl hAxisX;
 * Result = LCA_GetAxisHandle(hAxisSystem, 0, &hAxisX);
 * \endcode
 *
 * \note You can get the axis names and axis system names from the device
 * configuration files (see \ref ConfigFiles) that have been shipped with your
 * devices.
 *
 * \subsection MoCtrl_Step2 Step 2 - Enable devices
 * If you have valid device handles, you can start to bring your devices into a
 * properly enabled and initialized state. To do this, you need to:
 * 1. clear all faults (e.g. LCA_ClearAxisFault())
 * 2. enable all drives (LCA_Enable())
 * 3. execute the homing procedure to find the device homing positions
 * (LCA_FindHome())
 *
 * If you work with the multi axis functions, you simply need to call
 * LCA_FindHome(). This function will
 * - clear the axis faults of all devices that belong to the given axis system
 * - enable all axes of the axis system
 * - execute the homing procedure of the given axis system.
 *
 * After the homing procedure the device is properly initialized an you can
 * start with your normal motion control tasks.
 *
 * \subsection MoCtrl_InitExamples Examples
 * The following example code snippet shows a valid axis system initialization
 * procedure:
 * \includelineno AxisSystem_CAPI_Init.cpp
 *
 * \subsection MoCtrl_InitReference Reference
 * See the \ref lca_initialisation module for a detailed reference of all motion
 * control functions for initialization.
 *
 * ---
 *
 * \section MoCtrl_ProgrammingInterface Programming Interface - API
 * See the \ref lca_api module for a detailed reference of
 * the motion control library application programming interface
 *
 * \example AxisSystem_CAPI_Init.cpp Axis system initialization.
 * The following examples shows how to lookup, initialize and enable
 * an axis system and how to execute a homing move for all axes.
 *
 * \example capi_rotaxys_test.cpp
 * This test shows how to access the rotAXYS compact positioning device via
 * labbCAN \ref MotionControl. It demonstrates how to obtain valid device
 * handles and how to perform positioning tasks.
 *
 * \example capi_nemaxys_test.cpp
 * This test shows how to access the neMAXYS positioning device via
 * labbCAN \ref MotionControl. It demonstrates how to obtain valid device
 * handles and how to perform various positioning tasks.
 *
 * ---
 *
 * \section MotionControlAPI Programming Interface - API
 * See the \ref lca_api module for a detailed reference of
 * the motion control application programming interface
 */

/**
 * \addtogroup lca_api labbCAN Motion Control API
 * \brief Motion control specific functions.
 *
 * <img src="MenuItem_MotionControl_Library.png" align="left" style="padding-right: 10px;">
 * This module defines all labbCAN motion control specific functions,
 * identifiers and data types for driving labbCAN conform positioning systems
 * that are attached to a labbCAN software bus.
 * \see See \ref MotionControl for a detailed introduction and general
 *  overview of labbCAN motion control library.
 *
 * <div style="padding: 40px;"></div>
 * \{
 */


//===========================================================================
//                                 INCLUDES
//===========================================================================
#include "labbCAN_Bus_API.h"


//===========================================================================
//                                DEFINES
//===========================================================================
/// \cond private
#ifndef LCA_Func
	#define LCA_Func QMIXSDK_EXTERNC QMIXSDK_DLLIMPORT
#endif
#define LCA_CALLBACK QMIXSDK_CALLBACK
#define LCA_CALL QMIXSDK_CALL
/// \endcond


//---------------------------------------------------------------------------
/// \addtogroup lca_posunit Position Units
/// Defines common position units for all axis devices.
/// Whenever a user commands a movement then position parameters are always
/// given in the units defined by these identifiers. The units are based
/// on the standardized CANopen unit system
/// \{
#define METERS         1 ///< METERS
#define REVOLUTIONS  254 ///< REVOLUTIONS
#define DEGREE        65 ///< Angle in degrees (0 - 360)
#define RADIAN        16 ///< Angle in radian (0 - 2pi)
#define DEVICE         0 ///< use native device unit
/// \} lca_posunit


//---------------------------------------------------------------------------
/// \addtogroup lca_timeunit Time Units
/// Time unit identifies for velocity
/// \{
#define PER_SECOND    1 //!< PER_SECOND
#define PER_MINUTE   60 //!< PER_MINUTE
#define PER_HOUR   3600 //!< PER_HOUR
/// \} lca_timeunit


//---------------------------------------------------------------------------
/// \addtogroup lca_prefix Prefix Constants
/// Prefix constants for SI position and velocity unit specification
/// \{
#define UNIT   0 //!< use base unit
#define DECI  -1 //!< DECI
#define CENTI -2 //!< CENTI
#define MILLI -3 //!< MILLI
#define MICRO -6 //!< MICRO
/// \}  lca_prefix

/// \addtogroup lca_posunit Position Units
/// \{

//---------------------------------------------------------------------------
/// \addtogroup lca_posmark_edgetype Position Marker Edge Type
/// The following identifiers define on what kind of edge the position
/// should be captured.
/// \see LCA_WritePosMarkerEdgeType(), LCA_ReadPosMarkerEdgeType()
/// \{
//
/// \def POS_MARKER_EDGE_ALL 
/// Detects all edges. Digital Input State change from 0 to 1 or from 
/// 1 to 0.
//
/// \def POS_MARKER_EDGE_RISING 
/// Detects rising edges. Digital Input State change from 0 to 1
//
/// \def POS_MARKER_EDGE_FALLING 
/// Detects falling edges. Digital Input State change from 1 to 0
#define POS_MARKER_EDGE_ALL     0
#define POS_MARKER_EDGE_RISING  1
#define POS_MARKER_EDGE_FALLING 2
//
/// \} lca_posmark_edgetype


//---------------------------------------------------------------------------
/// \addtogroup lca_posmark_mode Position Marker Mode
/// The following identifiers define position marker-capturing mode.
/// \see LCA_WritePosMarkerMode(), LCA_ReadPosMarkerMode()
/// \{
//
/// \def POS_MARKER_MODE_CONTINUOUS 
/// On every detected edge (of correct kind) the position will be captured.
//
/// \def POS_MARKER_MODE_SINGLE 
/// Only the position at the first detected edge will be captured.
//
/// \def POS_MARKER_MODE_MULTIPLE 
/// The positions at the detected edges will be captured until the history 
/// buffer is full.
#define POS_MARKER_MODE_CONTINUOUS 0
#define POS_MARKER_MODE_SINGLE     1
#define POS_MARKER_MODE_MULTIPLE   2
/// \} lca_posmark_mode
/// \} lca_posmark

/// Use this velocity constant if you need maximum velocity
#define LCA_MAX_VELOCITY 0xFFFFFFFF


/**
 * Device property identifiers that can be used with the LCB_GetDeviceProperty()
 * and LCB_SetDeviceProperty() function to read and write certain device
 * properties.
 */
enum LCA_DeviceProperties
{
	/**
	 * Enables / disables safe rotation feature of rotAXYS device
	 * If this property is set to 1, the safe rotation feature is enabled.
	 * Rotation is only allowed, if the upper limit sensor is on - that
	 * means, if the lift axis is in its topmost position. If you call
	 * LCA_MoveToPosXY() if the sensor is not active, then the function returns
	 * the error code `ERR_PERM` (Not permitted) and XY movement is blocked.
	 */
	RotaxysPropertySafeRotation = 0,                 //!< RotaxysPropertySafeRotation

	/**
	 * This read only property returns the state of the upper limit sensor.
	 * Returns 1 if the sensor is on and 0 if the sensor is off
	 */
	RotaxysPropertyUpperLimitSensorState = 1,        //!< RotaxysPropertyUpperLimitSensorState

	/**
	 * The angle the rotAXYS360 device will never cross
	 */
	Rotaxys360PropertyRotationReversalAngleDegree = 2//!< Rotaxys360PropertyRotationReversalAngleDegree
};



//===========================================================================
//                     MOTION CONTROL API INITIALISATION
//
/// \addtogroup lca_api_initialisation API Initialization
/// API specific initialization functions.
/// This groups defines all functions to setup and initialize the labbCAN
/// axis system API properly.
/// \{
//===========================================================================


//---------------------------------------------------------------------------
/// Query number of detected axis systems.
/// Returns the number of all available axis systems.
/// \retval >= 0 Number of detected axis systems
/// \retval < 0  Error code
///
LCA_Func long LCA_CALL LCA_GetNoOfAxisSystems();


//---------------------------------------------------------------------------
/// Lookup an axis system by its name.
/// Each axissystem has an unique name. If an application knows the name of
/// a certain axissystem, then it can try to lookup an valid axis handle by
/// the of the axis system. Normally you will find all axis system names within
/// the property XML file.
/// \param[in] AxisSystemName Zero terminated axis name string
/// \param[out] AxisSystemHandle Handle to axis system device or 0 if no
///             axis system with given name exists
/// \retval -ERR_NODEV No device with the given name found
/// \retval ERR_NOERR indicates success
///
LCA_Func long LCA_CALL LCA_LookupAxisSystemByName(const char* AxisSystemName,
	dev_hdl* AxisSystemHandle);


//---------------------------------------------------------------------------
/// Get an axis system handle by its index.
/// \param[in] Index Index into list of available axis systems
/// \param[out] AxisSystemHandle Handle to axis system device or 0 if the given
///             index is out of range (>= LCA_GetNoOfAxisSystems())
/// \retval -ERR_PARAM_RANGE If the given device index is out of range
/// \retval ERR_NOERR indicates success
///
LCA_Func long LCA_CALL LCA_GetAxisSystemHandle(unsigned char Index,
	dev_hdl* AxisSystemHandle);


//---------------------------------------------------------------------------
/// Returns the number of axes of a certain axis system.
/// \param[in] hAxisSystem Valid axis system handle
/// \retval 0 No axis system with this index or invalid parameter
/// \retval >0 Number of axes
///
LCA_Func long LCA_CALL LCA_GetAxisSystemAxisNumber(dev_hdl hAxisSystem);


//---------------------------------------------------------------------------
/// Returns the number of available axes registered in the labbCAN environment.
/// \retval >=0 Number of available axes
/// \retval <0 Error code
///
LCA_Func long LCA_CALL LCA_AxisCount();


//---------------------------------------------------------------------------
/// Lookup an axis by its name.
/// Each axis has an unique name. If an application knows the name of
/// a certain axis then it can try to lookup an valid axis handle by the name
/// of the axis. Normally you will find all axis names within the property
/// XML file.
/// \param[in] pAxisName Zero terminated axis name string
/// \param[out] AxisHandle Handle to axis device or 0 if no
///             axis with given name exists
/// \retval -ERR_NODEV No device with the given name found
/// \retval ERR_NOERR indicates success
///
LCA_Func long LCA_CALL LCA_LookupAxisByName(const char *pAxisName,
	dev_hdl* AxisHandle);


//---------------------------------------------------------------------------
/// Get an handle for a certain axis
/// The functions LCB_ReadDevParam() and LCB_WriteDevParam() require a
/// valid device handle to read and write device specific parameters.
/// An axis system normally consists of a number of single axis devices.
/// In a CAN / CANopen environment these axis are single CAN nodes. Each
/// single axis contains its own set of parameters. The read and write
/// the parameters of single axis it is necessary to obtain a valid device
/// handle first to pass this handle into the functions LCB_ReadDevParam()
/// or LCB_WriteDevParam().
/// \param[in] hAxisSystem A valid axis system handle
/// \param[in] AxisId      Identifier of a single axis of the axis system
/// \param[out] AxisHandle Handle to axis device or 0 if the given
///             index is out of range (>= LCA_GetAxisSystemAxisNumber())
/// \retval -ERR_PARAM_RANGE If the given device index is out of range
///         (>= LCA_GetAxisSystemAxisNumber())
/// \retval ERR_NOERR indicates success
///
LCA_Func long LCA_CALL LCA_GetAxisHandle(dev_hdl hAxisSystem,
	unsigned char AxisId, dev_hdl* AxisHandle);
/// \} lca_api_initialisation


//===========================================================================
//                       AXIS SYSTEM INITIALISATION
//
/// \addtogroup lca_initialisation Axis System Initialization
/// Axis system specific initialization functions
/// This groups defines all functions to setup and initialize labCAN
/// axis systems properly.
/// \{
//===========================================================================


//---------------------------------------------------------------------------
/// Move all axis into its home position
/// The axis system should manage the order of the movement and should
/// know how to move all axis into a home state.
/// \param[in] hAxisSystem Valid axis system handle
/// \return Error code - ERR_NOERR indicates success
/// \note The function returns a soon as the homing move started. A
///       successfull return does not indicate, that the homing procedure was
///       successfull.
///
LCA_Func long LCA_CALL LCA_FindHome(dev_hdl hAxisSystem);


//---------------------------------------------------------------------------
/// Move single axis into its home position.
/// \param[in] hAxis Valid axis handle
/// \return Error code - ERR_NOERR indicates success
///
LCA_Func long LCA_CALL LCA_FindHomeOfAxis(dev_hdl hAxis);


//---------------------------------------------------------------------------
/// Set speed for move to homing or limit switch.
/// The function LCA_FindHome() or LCA_FindHomeOfAxis() execute homing moves
/// for a certain axis or a number axes. This function configures the speed
/// to use during this homing move if when axis searches for the homing or
/// limit switch.
/// \param[in] hAxis Valid axis handle
/// \param[in] fSpeed Speed value for search for homing or limit switch
/// \return Error code - ERR_NOERR indicates success
///
LCA_Func long LCA_CALL LCA_SetAxisHomingSwitchSpeed(dev_hdl hAxis,
                                                     double  fSpeed);

                                                     
//---------------------------------------------------------------------------
/// Set the home offset used for homing moves.
/// The home offset is a moving distance in homing procedure.
/// It is useful to move away from a detected position e.g. mechanical
/// border or limit switch at the end of the homing sequence.
/// This move could prevent the axis from a border damage resp. limit
/// switch error.
/// \param[in] hAxis Valid axis handle
/// \param[in] fOffset The home offset value in position units
/// \return Error code - ERR_NOERR indicates success
///
LCA_Func long LCA_CALL LCA_SetAxisHomingOffset(dev_hdl hAxis,
                                                double  fOffset);


//---------------------------------------------------------------------------
/// Set all axis of an axis system into enabled (operational) state
/// \param[in] hAxisSystem Valid axis system object handle
/// \return Error code - ERR_NOERR indicates success
///
LCA_Func long LCA_CALL LCA_Enable(dev_hdl hAxisSystem);


//---------------------------------------------------------------------------
/// Set single axis into enabled state.
/// \param[in] hAxis Valid axis handle
/// \return Error code - ERR_NOERR indicates success
///
LCA_Func long LCA_CALL LCA_EnableAxis(dev_hdl hAxis);


//---------------------------------------------------------------------------
/// Set all axis of an axis system into disabled state.
/// You have to be carefull if you set axis system into disabled state.
/// If an axis is set disabled, the voltage is switched of so there is no
/// force on an axis and if it is a vertical axis the axis may move because
/// of gravity.
/// \param[in] hAxisSystem Valid axis system object handle
/// \return Error code - ERR_NOERR indicates success
///
LCA_Func long LCA_CALL LCA_Disable(dev_hdl hAxisSystem);


//---------------------------------------------------------------------------
/// Set a certain axis of an axis system into disabled state.
/// You have to be careful if you set axis system into disabled state.
/// If an axis is set disabled, the voltage is switched of so there is no
/// force on an axis and if it is a vertical axis the axis may move because
/// of gravity.
/// \param[in] hAxis Valid axis handle
/// \return Error code - ERR_NOERR indicates success
///
LCA_Func long LCA_CALL LCA_DisableAxis(dev_hdl hAxis);


//---------------------------------------------------------------------------
/// Clear fault condition.
/// This is some kind of error acknowledge that clears the last fault and
/// sets the device in an error free state
/// \param[in] hAxis Valid axis handle
/// \return Error code - ERR_NOERR indicates success
///
LCA_Func long LCA_CALL LCA_ClearAxisFault(dev_hdl hAxis);

//---------------------------------------------------------------------------
/// Query the value of the internal axis position counter.
/// \see LCA_RestoreAxisPosCnt()
/// \param[in] hAxis Valid axis handle
/// \param[out] pPosCntValue Returns the actual value of the position
///                          counter
/// \return Error code - ERR_NOERR indicates success
///
LCA_Func long LCA_CALL LCA_GetAxisPosCnt(dev_hdl hAxis, long *pPosCntValue);


//---------------------------------------------------------------------------
/// Restore internal hardware position counter value.
/// The function restores the internal position counter value
/// saved with LCA_GetAxisPosCnt().
/// \note In many axis systems the actual position value is countet by a
/// quadrature decoder. This internal position counter value will get
/// lost, as soon as the device is switched off. In order to restore
/// this positon counter value after power on, an application can
/// query the internal position counter value (LCA_GetAxisPosCnt()), store
/// it persistenly into a configuration file and restore it later by calling
/// this function.
/// \see LCA_GetAxisPosCnt()
/// \param[in] hAxis Valid axis handle
/// \param[in] PosCntValue The position counter value to restore
/// \return Error code - ERR_NOERR indicates success
///
LCA_Func long LCA_CALL LCA_RestoreAxisPosCnt(dev_hdl hAxis, long PosCntValue);

/// \} lca_initialisation



//===========================================================================
//                       AXIS SYSTEM CONFIGURATION
//
/// \addtogroup lca_configuration Axis System Configuration
/// Axis system configuration functions
/// This groups defines all functions to configure labCAN axis systems
/// properly.
/// \{
//===========================================================================

//---------------------------------------------------------------------------
/// Set default position unit.
/// This function sets the default position unit. All parameters of subsequent
/// move function calls are given in this new unit. Example to select
/// millimeters as position unit. Example:
/// \code
/// long Result = LCA_SetDefaultPosUnit(hAxis, MILLI, METERS);
/// \endcode
/// \param[in] hAxis Valid axis handle
/// \param[in] Prefix The prefix of the SIunit (i.e MILLI - see @ref lca_prefix)
/// \param[in] PositionUnit The position unit identifier (i.e. METERS - see @ref
///            lca_posunit)
/// \return Error code - ERR_NOERR indicates success
/// \warning Take care if you work with axis systems. Axis systems may rely on
/// a certain position and velocity unit of their axis devices. If you change
/// the position unit or velocity unit, you should restore the default unit
/// prior to using the axis system functions.
///
LCA_Func long LCA_CALL LCA_SetDefaultPosUnit(dev_hdl hAxis,
                                              int    Prefix,
                                              int     PositionUnit);


//---------------------------------------------------------------------------
/// Queries the default position unit.
/// \param[in] hAxis Valid axis handle
/// \param[out] pPrefix Returns the prefix of the SIunit
///             (i.e MILLI - see @ref lca_prefix)
/// \param[out] pPositionUnit Returns the position unit identifier
///            (i.e. METERS - see @ref lca_posunit)
/// \return Error code - ERR_NOERR indicates success
///
LCA_Func long LCA_CALL LCA_GetDefaultPosUnit(dev_hdl hAxis,
	                                          int*   pPrefix,
                                              int*    pPositionUnit);


//---------------------------------------------------------------------------
/// Set default velocity unit.
/// This function sets the default velocity unit.
/// \code
/// long Result = LCA_SetDefaultVelUnit(hAxis, MILLI, METERS, PER_SECOND);
/// \endcode
/// \param[in] hAxis Valid axis handle
/// \param[in] Prefix The prefix of the velocity unit (see @ref lca_prefix)
/// \param[in] PositionUnit The position unit (numerator) of the velocity
///            unit (i.e. METERS - see @ref lca_posunit)
/// \param[in] TimeUnit The time unit (denominator) of the velocity unit.
///            (i.e. PER_SECOND - see @ref lca_timeunit)
/// \return Error code - ERR_NOERR indicates success
/// \warning Take care if you work with axis systems. Axis systems may rely on
/// a certain position and velocity unit of their axis devices. If you change
/// the position unit or velocity unit, you should restore the default unit
/// prior to using the axis system functions.
///
LCA_Func long LCA_CALL LCA_SetDefaultVelUnit(dev_hdl hAxis,
                                              int    Prefix,
                                              int     PositionUnit,
                                              int     TimeUnit);


//---------------------------------------------------------------------------
/// Queries the default velocity unit.
/// \param[in] hAxis Valid axis handle
/// \param[out] pPrefix Returns the prefix of the velocity unit (see @ref lca_prefix)
/// \param[out] pPositionUnit Returns the position unit (numerator) of the
///             velocity unit (i.e. METERS - see @ref lca_posunit)
/// \param[out] pTimeUnit Returns the time unit (denominator) of the velocity
///             unit. (i.e. PER_SECOND - see @ref lca_timeunit)
/// \return Error code - ERR_NOERR indicates success
///
LCA_Func long LCA_CALL LCA_GetDefaultVelUnit(dev_hdl hAxis,
                                              int*   pPrefix,
                                              int*    pPositionUnit,
                                              int*    pTimeUnit);


//---------------------------------------------------------------------------
/// Query minimum position limit for axis.
/// The travel range of the axis is the range between minimum and maximum
/// position.
/// \param[in] hAxis Valid axis handle
/// \param[out] pfPosMin Stores maximum axis position in position units
/// \return The maximum position in position units
/// \see LCA_GetAxisPosMax()
///
LCA_Func long LCA_CALL LCA_GetAxisPosMin(dev_hdl hAxis,
                                          double* pfPosMin);
                                              

//---------------------------------------------------------------------------
/// Query maximum position limit for axis.
/// The travel range of the axis is the range between minimum and maximum
/// position.
/// \param[in] hAxis Valid axis handle
/// \param[out] pfPosMax Stores maximum axis position in position units
/// \return The maximum position in position units
/// \see LCA_GetAxisPosMin()
///
LCA_Func long LCA_CALL LCA_GetAxisPosMax(dev_hdl hAxis,
                                          double* pfPosMax);


//--------------------------------------------------------------------------
/// Query maximum velocity for axis.
/// The minimum velocity is considered 0
/// \param[in] hAxis Valid axis handle
/// \param[out] pfVelMax Stores maximum axis velocity in velocity units
/// \return The maximum velocity in velocity units
///
LCA_Func long LCA_CALL LCA_GetAxisVelMax(dev_hdl hAxis,
                                          double* pfVelMax);

                                          
//--------------------------------------------------------------------------
/// Query speed for move to homing or limit switch.
/// The function LCA_FindHome() or LCA_FindHomeOfAxis() execute homing moves
/// for a certain axis or a number axes. This function reads the speed
/// used during this homing move while axis searches for the home switch or
/// limit switch.
/// \param[in] hAxis Valid axis handle
/// \param[out] pfSpeed Returns speed value for limit switch search
/// \return Error code - ERR_NOERR indicates success
///
LCA_Func long LCA_CALL LCA_GetAxisHomingSwitchSpeed(dev_hdl hAxis,
                                                     double* pfSpeed);

/// \} lca_configuration



//===========================================================================
//                       AXIS SYSTEM MOVEMENT
//
/// \addtogroup lca_motion Motion
/// Motion functions for moving single axes or the whole positioning system.
/// This groups defines all functions to perform certain motion tasks like
/// moving single axis, moving multiple axes.
/// \{
//===========================================================================


//---------------------------------------------------------------------------
/// Moves XY positioning system to a certain XY position if coordinate space.
/// This function is important for axis system that needs to do some coordinate
/// translation. I.e. the rotAXYS positioning system needs to translate between
/// polar coordinates and cartesian coordinates. So for moving in XY cartesian
/// coordinate space, you can't use the axis functions.
/// \param[in] hAxisSystem Valid axis system handle
/// \param[in] fPositionX Absolute X position value in position units
/// \param[in] fPositionY Absolute Y position value in position units
/// \param[in] fVelocity Velocity value from  0 - 1. The velocity value
///                      is multiplied with the maximum velocity value of each
///                      axis. So a value of 1 means, all axes travel with their
///                      maximum velocity. A value of 0.5 means, all axes travel
///                      with the half of the maximum velocity.
/// \param[in] PrivData Additional data that may additional drive specific
///                     parameters
///
/// \return Error code - ERR_NOERR indicates success
/// \note A velocity value of <=0 and >1 is not valid and will cause an error
/// \see LCA_GetActualPostitionXY()
///
LCA_Func long LCA_CALL LCA_MoveToPosXY(dev_hdl       hAxisSystem,
                                        double        fPositionX,
                                        double        fPositionY,
                                        double        fVelocity,
                                        unsigned long PrivData);


//---------------------------------------------------------------------------
/// Move axis to a certain absolute position with a certain velocity.
/// \param[in] hAxis Valid axis handle
/// \param[in] fPosition Absolute position value in position units
/// \param[in] fVelocity Velocity value for the movement
/// \param[in] PrivData Additional data that may additional drive specific
///                     parameters
///
/// \return Error code - ERR_NOERR indicates success
///
LCA_Func long LCA_CALL LCA_MoveToPos(dev_hdl       hAxis,
                                      double        fPosition,
                                      double        fVelocity,
                                      unsigned long PrivData);

                                      
//---------------------------------------------------------------------------
/// Move a certain distance with an axis.
/// Executes a relative position move in one or another direction. The
/// \param[in] hAxis Valid axis handle
/// \param[in] fDistance   Relative position value in position units
/// \param[in] fVelocity   Velocity value for the movement
/// \param[in] PrivData    Additional data that may additional drive specific
///                        parameters
///
/// \return Error code - ERR_NOERR indicates success
///
LCA_Func long LCA_CALL LCA_MoveDistance(dev_hdl       hAxis,
                                         double        fDistance,
                                         double        fVelocity,
                                         unsigned long PrivData);

                                         
//---------------------------------------------------------------------------
/// Move an axis with a certain velocity.
/// Moves an axis with a certain velocity until the maximum or minimum
/// position is reached. The function uses the default velocity unit.
/// \param[in] hAxis Valid axis handle
/// \param[in] fVelocity   Velocity value for the movement - a negative value
///                        moves the axis towards the minimum position, a
///                        positive velocity moves the axis to the maximum
///                        position.
/// \param[in] PrivData    Additional data that may additional drive specific
///                        parameters
///
/// \return Error code - ERR_NOERR indicates success
///
LCA_Func long LCA_CALL LCA_MoveWithVelocity(dev_hdl       hAxis,
                                             double        fVelocity,
                                             unsigned long PrivData);


//---------------------------------------------------------------------------
/// Stop movement of axis system - send stop command to all axis system axes.
/// This stops the motion of the axis by executing the deceleration
/// ramp.
/// \param[in] hAxisSystem Valid axis system handle
/// \return Error code - ERR_NOERR indicates success
///
LCA_Func long LCA_CALL LCA_StopMove(dev_hdl hAxisSystem);


//---------------------------------------------------------------------------
/// Stop axis movement of a single axis.
/// This stops the motion of the axis by executing the deceleration
/// ramp.
/// \param[in] hAxis Valid axis handle
/// \return Error code - ERR_NOERR indicates success
///
LCA_Func long LCA_CALL LCA_StopMoveOfAxis(dev_hdl hAxis);

/// \} lca_motion




//===========================================================================
//                      AXIS SYSTEM STATUS INFORMATION
//
/// \addtogroup lca_status Status
/// Status query functions.
/// This groups defines all functions to query the status of single axes
/// or the status of the whole axis system
/// \{
//===========================================================================


//---------------------------------------------------------------------------
/// Query the actual XY position of the axis system.
/// Some axis systems, i.e. rotAXYS, needs to do some translation between its
/// axis coordinates (polar coordinates) and the XY cartesian coordinates.
/// It is not possible to use the axis functions directly in this cas
/// \param[in]  hAxisSystem Valid axis system handle
/// \param[out] pfPosIsX  Stores actual X position
/// \param[out] pfPosIsY  Stores actual Y position
/// \return Error code - ERR_NOERR indicates success
/// \see LCA_MoveToPosXY()
///
LCA_Func long LCA_CALL LCA_GetActualPostitionXY(dev_hdl hAxisSystem,
                                                 double* pfPosIsX,
                                                 double* pfPosIsY);


//---------------------------------------------------------------------------
/// Query the actual position of the axis.
/// \param[in] hAxis Valid axis handle
/// \param[out] pfPosIs     Stores actual position of the axis
/// \return Error code - ERR_NOERR indicates success
///
LCA_Func long LCA_CALL LCA_GetAxisPosIs(dev_hdl hAxis,
                                         double* pfPosIs);


//---------------------------------------------------------------------------
/// Query actual speed of the axis.
/// \param[in] hAxis Valid axis handle
/// \param[out] pfVelIs Returns the actual velocity of the axis
/// \return Error code - ERR_NOERR indicates success
///
LCA_Func long LCA_CALL LCA_GetAxisVelIs(dev_hdl hAxis,
                                         double* pfVelIs);


//---------------------------------------------------------------------------
/// Query if axis is enabled.
/// Only if the axis is enable it is possible to execute moves
/// \param[in] hAxis Valid axis handle
/// \retval > 0 Axis is enabled
/// \retval = 0 Axis is disabled
/// \retval < 0 Error code
///
LCA_Func long LCA_CALL LCA_IsAxisEnabled(dev_hdl hAxis);


//---------------------------------------------------------------------------
/// Check if axis is in a fault state.
/// \param[in] hAxis Valid axis handle
/// \retval > 0 Axis is in fault state
/// \retval = 0 Axis is not in fault state
/// \retval < 0 Error code
///
LCA_Func long LCA_CALL LCA_IsAxisInFaultState(dev_hdl hAxis);


//---------------------------------------------------------------------------
/// Check if drive is stopped or if it is moving.
/// \param[in] hAxis Valid axis handle
/// \retval > 0 Axis is stopped
/// \retval = 0 Axis is moving
/// \retval < 0 Error code
///
LCA_Func long LCA_CALL LCA_IsAxisStopped(dev_hdl hAxis);


//---------------------------------------------------------------------------
/// Check if an axis system reached its target position.
/// The target position is reached, if all axis devices of an axis system
/// reached their target positions.
/// \param[in] hAxisSystem Valid axissysem handle
/// \retval > 0 Axis reached its target position
/// \retval = 0 Axis did not reach its target position yet
/// \retval < 0 Error code
///
LCA_Func long LCA_CALL LCA_IsTargetPosReached(dev_hdl hAxisSystem);


//---------------------------------------------------------------------------
/// Check if device reached its target position.
/// \param[in] hAxis Valid axis handle
/// \retval > 0 Axis reached its target position
/// \retval = 0 Axis did not reach its target position yet
/// \retval < 0 Error code
///
LCA_Func long LCA_CALL LCA_IsAxisTargetPosReached(dev_hdl hAxis);


//--------------------------------------------------------------------------
/// Check if homing position of the given axis system is attained.
/// Homing it attained, if all axes reached their homing positions
/// \param[in] hAxisSystem Valid axis system handle
/// \retval > 0 Axis reached its homing position
/// \retval = 0 Axis did not reach its homing position
/// \retval < 0 Error code
///
LCA_Func long LCA_CALL LCA_IsHomingPosAttained(dev_hdl hAxisSystem);


//--------------------------------------------------------------------------
/// Check if homing is attained by device.
/// \param[in] hAxis Valid axis handle
/// \retval > 0 Axis reached its homing position
/// \retval = 0 Axis did not reach its homing position
/// \retval < 0 Error code
///
LCA_Func long LCA_CALL LCA_IsAxisHomingPosAttained(dev_hdl hAxis);
/// \} lca_status



//===========================================================================
//                            ERROR HANDLING
//
/// \addtogroup lca_error Error Handling
/// Error handling functions.
/// This groups defines all functions to handle axis system specific
/// device errors.
/// \{
//===========================================================================

//---------------------------------------------------------------------------
/// Query last occurred error code.
/// If device is in error state (LCA_IsAxisInFaultState()) then this function
/// returns the last error that occurred.
/// \param[in] hAxis Valid axis handle
/// \param[out] pLastDevErr Returns the last error that occurred
/// \return Error code - ERR_NOERR indicates success
///
LCA_Func long LCA_CALL LCA_ReadLastAxisDevErr(dev_hdl hAxis, long *pLastDevErr);


//---------------------------------------------------------------------------
/// Get descriptive error message for a certain device error that cured.
/// \param[in] hAxis Valid axis handle
/// \param[in]  DevErr      Error code of device error that occurred
/// \param[out] pStringBuf  String buffer for storage of error message
/// \param[in]  BufSize     Size of string buffer in bytes
/// \return Error code - ERR_NOERR indicates success
///
LCA_Func long LCA_CALL LCA_GetDevErrMsg(dev_hdl        hAxis,
                                         long           DevErr,
                                         char          *pStringBuf,
                                         short          BufSize);

/// \} lca_error


//============================================================================
//                      POSITION MARKER FUNCTIONALITY
//
/// \addtogroup lca_posmark Position Marker
/// Position marker functionality.
/// This group defines all functions to configure and read the position
/// marker. A position marker is a captured position value. Some motion
/// control devices support capturing of internal position values on
/// change of a digital input. This function group supports the setup,
/// configuration and use of a position marker. If a device does not support
/// the position marker interface then the following functions will
/// return -ERR_NOSUPP. Normally a position marker consists of a digital input
/// that triggers position capturing, a position capture history and a certain
/// Position capture configuration. The position capture history is a kind of an
/// array that stores the captured positions. The newest position is always at
/// array index position 0 and the older positions are following on
/// higher array indices.
/// \{
//
/// \example PositionMarker_CAPI.cpp
/// This example shows how to use the position marker in continuous mode.
//============================================================================


//----------------------------------------------------------------------------
/// Check if a certain axis supports position marker functionality.
/// \param[in] hAxis Valid axis handle
/// \retval <0 Error code
/// \retval  0 Position marker functionality not supported
/// \retval  1 Position marker functionality supported
///
LCA_Func long LCA_CALL LCA_IsPosMarkerSupported(dev_hdl hAxis);


//----------------------------------------------------------------------------
/// Reads the number of detected edges from device.
/// The position counter counts the number of detected edges / the number
/// of captured positions. This function returns the number of captured
/// positions.
/// \param[in] hAxis Valid axis handle
/// \param[out] pPosCounter The position counter value read from device
/// \return Error code - ERR_NOERR
///
LCA_Func long LCA_CALL LCA_ReadPosMarkerCounter(dev_hdl         hAxis,
                                                 unsigned short *pPosCounter);


//----------------------------------------------------------------------------
/// Clear captured positions.
/// This functions clears the list of captured positions and resets
/// the position counter to 0.
/// \param[in] hAxis Valid axis handle
/// \return Error code - ERR_NOERR indicates success
///
LCA_Func long LCA_CALL LCA_ClearCapturedPositions(dev_hdl hAxis);


//----------------------------------------------------------------------------
/// Query size of position history.
/// The size of the position history indicates how many positions
/// can be captured before the first position will be overwritten by a
/// new position value. The positions should be read before this
/// happens.
/// \param[in] hAxis Valid axis handle
/// \retval <0  Error
/// \retval >0  Position history size
///
LCA_Func long LCA_CALL LCA_GetPositionHistorySize(dev_hdl hAxis);


//----------------------------------------------------------------------------
/// Read captured position from device.
/// The position marker function holds a history of captured positions
/// in an array. The newest position is always at array index 0. If more then
/// one position is captured in "multiple capture mode" or "continuous capture
/// mode" the older captured positions will be shifted to the next array index.
/// \note If the number of captured positions is more than the size of the
///       position array in "continuous capture mode" the oldest marker
///       positions are lost.
/// \param[in] hAxis Valid axis handle
/// \param[in] PosHistoryIndex Index into list of captured positions
/// \param[out] pfCapturedPosition The captured position read from list
/// \return Error code - ERR_NOERR indicates success
///
LCA_Func long LCA_CALL LCA_ReadCapturedPosition(dev_hdl        hAxis,
                                                 unsigned short  PosHistoryIndex,
                                                 double        *pfCapturedPosition);

                                                 
//----------------------------------------------------------------------------
/// Configure the edge type for position capturing.
/// \param[in] hAxis Valid axis handle
/// \param[in] EdgeType Edge type
/// \return Error code - ERR_NOERR indicates success
/// \see lca_posmark_edgetype
///
LCA_Func long LCA_CALL LCA_WritePosMarkerEdgeType(dev_hdl       hAxis,
                                                   unsigned short EdgeType);


//----------------------------------------------------------------------------
/// Reads the edge type for position capturing from device.
/// \param[in] hAxis Valid axis handle
/// \param[out] pEdgeType Edge type
/// \return Error code - ERR_NOERR indicates success
/// \see lca_posmark_edgetype
///
LCA_Func long LCA_CALL LCA_ReadPosMarkerEdgeType(dev_hdl        hAxis,
                                                  unsigned short *pEdgeType);


//----------------------------------------------------------------------------
/// Configures the capturing mode.
/// \param[in] hAxis Valid axis handle
/// \param[in] Mode The capturing mode to use
/// \return Error code - ERR_NOERR indicates success
/// \see lca_posmark_mode
///
LCA_Func long LCA_CALL LCA_WritePosMarkerMode(dev_hdl       hAxis,
                                               unsigned short Mode);


//----------------------------------------------------------------------------
/// Reads the capturing mode from device.
/// \param[in] hAxis Valid axis handle
/// \param[out] pMode Stores the capturing mode
/// \return Error code - ERR_NOERR indicates success
/// \see lca_posmark_mode
///
LCA_Func long LCA_CALL LCA_ReadPosMarkerMode(dev_hdl        hAxis,
                                              unsigned short *pMode);
/// \} lca_posmark
/// \} lca_api

//---------------------------------------------------------------------------
#endif // labbCAN_MotionControl_APIH

