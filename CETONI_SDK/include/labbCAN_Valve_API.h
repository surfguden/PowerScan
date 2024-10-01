#ifndef labbCAN_Valve_APIH
#define labbCAN_Valve_APIH
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
/// \file   labbCAN_Valve_API.h
/// \author Uwe Kindler
/// \date   13.07.2012
/// \brief  Declaration of labbCAN_Valve_API
//
//===========================================================================

/**
 * \page ValveAPI Valve Library
 * \ifnot bootstrap
 *    \tableofcontents
 *    <img src="Slider_Valve_API_color.jpg" align="center" style="padding-right: 10px; width: 800px;">
 * \else
 *    \image html Slider_Valve_API_color.jpg
 * \endif
 * \section ValveAPI_Introduction Introduction
 * This valve library defines a common valve control interface for a
 * range of different valve types such as e.g. rotation valves, switch
 * valves or pinch valves.
 *
 * ---
 *
 * \section ValveAPI_Including Including
 * The way how you include the library functions in your own windows program,
 * depends on the compiler and on the programming language you use. In order to
 * access the valve API, you have to include the library
 * **labbCAN_Valve_API.dll** to your programming environment. You have
 * to copy this file to the working directory of your system or to the
 * application directory that contains your application EXE file.
 * Use the calling convention \b LCV_CALL for this library. This convention
 * is managing how the parameters are put on the stack and who is responsible
 * to clean the stack after the function execution.
 *
 * The interface of the library, constant definitions and declarations of the
 * library functions, is defined in the header file
 * \link labbCAN_Valve_API.h interface/labbCAN_Valve_API.h \endlink
 *
 * ---
 *
 * \section ValveAPI_Usage Valve API Usage
 * \subsection ValveAPI_Step1 Retrieve device handle
 * To work with a valve, you need a valid device handle. A device handle is
 * simply an opaque pointer to the internal device object created by the
 * labbCAN environment. So the first thing you need do to is obtaining a valid
 * device handle.
 *
 * You can get a valid valve handle with the functions
 * LCV_LookupValveByName() or LCV_GetValveHandle():
 * \code
 * dev_hdl ValveHandle;
 * Result = LCV_LookupValveByName("Nemesys1_Valve", &ValveHandle);
 * dev_hdl ValveHandle2;
 * Result = LCV_GetValveHandle(1, &ValveHandle2);
 * \endcode
 *
 * \note You can get the valve names from the device configuration files (see
 * \ref ConfigFiles)
 *
 * \subsection ValveAPI_Step2 Switching valve
 * Each valve position is identified by a logical valve position identifier
 * from 0 - number of valve positions - 1. To switch the valve to a certain
 * valve position, you simply call LCV_SwitchValveToPosition() with a valid
 * logical valve position index. The following example switches the valve
 * identified by valve handle hValve1 to the logical valve position 2.
 *
 * \code
 * long Result = LCV_SwitchValveToPosition(hValve1, 2);
 * \endcode
 *
 * \subsection ValveAPI_Step3 Reading actual valve position
 * You can easily query the actual valve position with the function
 * LCV_ActualValvePosition().
 *
 * \code
 * long ActualValvePosition = LCV_ActualValvePosition(hValve1);
 * \endcode
 *
 * \subsection ValveAPI_Reference Reference
 * See the \ref lcv_api module for a detailed reference of all valve control
 * and status functions.
 *
 * ---
 *
 * \section ValveAPI_ProgrammingInterface Programming Interface - API
 * See the \ref lcv_api module for a detailed reference of
 * the valve library application programming interface
 *
 * \example capi_nemesys_valve_test.cpp
 * The valve C-API test implementation shows how to access valve devices via
 * \ref ValveAPI. It demonstrates how to retrieve valid valve device handles
 * and how to switch valves and read valve positions.
 */

/**
 * \addtogroup lcv_api labbCAN Valve API
 * <img src="MenuItem_Valve_Library.png" align="left" style="padding-right: 10px;">
 * \brief Valve specific functions.
 * The **Valve API** contains Valve specific functions for common access
 * to all valve device (rotation valves, switch valves) attached to the labbCAN
 * software bus.
 *  \see See \ref ValveAPI for a detailed introduction and general overview of
 *  labbCAN valve library.
 *
 *  <div style="padding: 40px;"></div>
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
#ifndef LCV_Func
	#define LCV_Func QMIXSDK_EXTERNC QMIXSDK_DLLIMPORT
#endif
#define LCV_CALLBACK QMIXSDK_CALLBACK
#define LCV_CALL QMIXSDK_CALL
/// \endcond



//===========================================================================
//                     VALVE API INITIALISATION
//
/// \addtogroup lcv_api_init Valve API Initialization
/// This groups defines all functions to retrieve valid valve device handles
/// from the labbCAN valve library
/// \{
//===========================================================================

//---------------------------------------------------------------------------
/// Query number of detected valve devices
/// \retval >= 0 Number of detected valve devices
/// \retval < 0  Error code
///
LCV_Func long LCV_CALL LCV_GetNoOfValves();


//---------------------------------------------------------------------------
/// Lookup for a valve device by its name.
/// \param[in] pValveName The name of the device to lookup for
/// \param[out] ValveHandle Handle to valve device or 0 if no valve with given
///             name exists
/// \retval -ERR_NODEV No device with the given name found
/// \retval ERR_NOERR indicates success
///
LCV_Func long LCV_CALL LCV_LookupValveByName(const char *pValveName,
	dev_hdl* ValveHandle);


//---------------------------------------------------------------------------
/// Get valve handle by its index.
/// \param[in] Index Index into list of available valve devices
/// \param[out] ValveHandle Handle to valve device or 0 if the given index is
///             out of range
/// \retval -ERR_PARAM_RANGE If the given device index is out of range
/// \retval ERR_NOERR indicates success
///
LCV_Func long LCV_CALL LCV_GetValveHandle(unsigned char Index,
	dev_hdl* ValveHandle);
/// \} lcp_api_init


//===========================================================================
//                        VALVE CONTROL & STATUS
//
/// \addtogroup lcv_control Valve Control and Status
/// This groups defines all functions for control of valves and for reading
/// valve status.
/// \{
//===========================================================================

//---------------------------------------------------------------------------
/// Returns the number of valve positions.
/// Each valve has a number of available valve positions. I.e. a switching
/// valve has two positions or a rotation valve can have 4 or even more
/// positions.
/// \param[in] hValve Valid valve handle
/// \retval >0 Number of valve positions
/// \retval <=0 Error code
///
LCV_Func long LCV_CALL LCV_NumberOfValvePositions(dev_hdl hValve);


//---------------------------------------------------------------------------
/// Returns the actual logical valve position.
/// Each valve position is identified by a logical valve position identifier
/// from 0 - number of valve positions - 1. This function returns the logical
/// valve position identifier for the current valve position.
/// \param[in] hValve Valid valve handle
/// \retval >=0 Actual valve position index.
/// \retval <0 Error code
/// \see LCV_SwitchValveToPosition()
///
LCV_Func long LCV_CALL LCV_ActualValvePosition(dev_hdl hValve);


//---------------------------------------------------------------------------
/// Switches the valve to a certain logical valve position.
/// \note For some devices, like rotation valves, it may last some hundred
///       milliseconds until device reached its final position.
/// \param[in] hValve Valid valve handle
/// \param[in] LogicalValvePosition Logical valve target position index.
/// \retval ERR_NOERR indicates success
/// \see LCV_ActualValvePosition();
///
LCV_Func long LCV_CALL LCV_SwitchValveToPosition(dev_hdl hValve,
	                                              int     LogicalValvePosition);

/// \} lcv_control
/// \} lcv_api

//---------------------------------------------------------------------------
#endif // labbCAN_Valve_APIH
