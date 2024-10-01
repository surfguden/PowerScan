#ifndef labbCAN_Bus_APIH
#define labbCAN_Bus_APIH
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
/// \file     labbCAN_Bus_API.h
/// \author   Uwe Kindler (UK)
/// \date     2015/09/09
/// \brief    labbCAN Bus Application Programming Interface
//
//===========================================================================



/**
 *  \addtogroup lcb_api labbCAN Bus API
 *  \brief Common bus specific functions, types and identifiers.
 *
 *  <img src="MenuItem_Bus_Library.png" align="left" style="padding-right: 10px;">
 *  This module defines all labCAN bus specific functions for initialization,
 *  management and error / event handling when using a labbCAN bus.
 *  \see See \ref index for a detailed introduction and overview.
 *
 *  <div style="padding: 40px;"></div>
 *  \{
 */

//===========================================================================
//                                DEFINES
//===========================================================================
/// \cond private
#if defined(_WIN32) || defined(_WIN64)
	#define QMIXSDK_DLLEXPORT __declspec (dllexport)
	#define QMIXSDK_DLLIMPORT __declspec (dllimport)
	#define QMIXSDK_CALLBACK __cdecl
	#define QMIXSDK_CALL __stdcall
#else
	#define QMIXSDK_DLLEXPORT
	#define QMIXSDK_DLLIMPORT
	#define QMIXSDK_CALLBACK
	#define QMIXSDK_CALL
#endif

#ifdef __cplusplus
	#define QMIXSDK_EXTERNC extern "C"
#else
	#define QMIXSDK_EXTERNC
#endif

#ifndef LCB_Func
	#define LCB_Func QMIXSDK_EXTERNC QMIXSDK_DLLIMPORT
#endif
#define LCB_CALLBACK QMIXSDK_CALLBACK
#define LCB_CALL QMIXSDK_CALL
/// \endcond



/// \addtogroup lcb_error Error and Event Handling
/// @{
//---------------------------------------------------------------------------
/**
 * \enum LCB_EventId
 * Event identifier returned in EventId when reading event queue via
 * LCB_ReadEventEx().
 * \example capi_event_queue_test.cpp Event queue reading demo
 */

/**
 * \var LCB_EventId::LCB_EVENT_DATA_LINK_LAYER
 * Data link layer event.
 * These are events that occur in the data link layer - e.g. if the interface
 * is disconnected or if the data transfer fails for some reason.
 * The data that is returned if the first data field of LCB_ReadEventEx()
 * contains the error code or the error that occurred. You can pass this
 * error to LCB_GetErrMsg() to get a human readable error message.
 * This event returns the following data:
 *    - pData1 - Data link layer error code
 */

/**
 * \var LCB_EventId::LCB_EVENT_ERR
 * Error event - an error occurred.
 * You can pass this error to LCB_GetErrMsg() to get a human readable error message.
 * This event returns the following data:
 *    - pData1 - Emergency error code
 */

/**
 *  \var LCB_EventId::LCB_EVENT_DEVICE_EMERGENCY
 *  Device specific emergency event.
 *   Identifies device specific emergency messages. Devices use emergency
     events to indicate failures and unexpected events. This event returns
     the following data:
     - pDeviceHandle - Device handle of device that caused the emergency event
     - pData1 - Emergency error code

     You can use the device handle for functions that required a device
     handle. You can call LCB_GetDevErrMsg() with the device handle and the
     emergency error code as parameter to get a descriptive error message
     string for the emergency error returned in pData1
 */


/**
 * \var LCB_EventId::LCB_EVENT_DEVICE_GUARD
 * A guarding event (nodeguard or heartbeat) occurred.
 * This event returns the following data:
 * 	- pDeviceHandle - Device handle of device that caused guard event
 * 	- pData1 - Guard event id \ref LCB_GuardEventId
 */
enum LCB_EventId
{
	LCB_EVENT_DATA_LINK_LAYER     = 2,
	LCB_EVENT_ERR                 = 4,
	LCB_EVENT_DEVICE_EMERGENCY    = 5,
	LCB_EVENT_DEVICE_GUARD        = 6,
};


/**
 * Guard event identifier that is returned in the first data field if the
 * event type is \ref LCB_EVENT_DEVICE_GUARD.
 * Devices can be monitored by the means of the Node Guarding Protocol or
 * the Heartbeat Protocol.
 * See https://www.can-cia.org/can-knowledge/canopen/error-control-protocols/
 * for details. If a guarding error occurs, this is identified by this ID.
 */
enum LCB_GuardEventId
{
    NODEGUARD_ERR_OCCURED = 0,//!< node guard error occurred - device did not respond
    NODEGUARD_ERR_RESOLVED,   //!< node guard error resolved
    HEARTBEAT_ERR_OCCURED,    //!< heartbeat error occurred
    HEARTBEAT_ERR_RESOLVED,   //!< heartbeat error resolved
    NODESTATE_ERR,            //!< node state error
    NODESTATE_CHANGED,        //!< node state changed
};
/// @} lcb_error


/// \addtogroup lcb_device Device Management
/// @{
/**
 * Communication state identifiers for LCB_SetCommState()
 */
enum LCB_CommState
{
	LCB_COMM_STOPPED      = 0x02, ///< no process data communication
	LCB_COMM_CONFIGURABLE = 0x80, ///< for configuration purposes - preoperational
	LCB_COMM_OPERATIONAL  = 0x01, ///< full communication - some parameters are not writable in this state
};
/// @} lcb_device


//===========================================================================
//                                  DATA TYPES
//===========================================================================
typedef long long labb_hdl;///< generic labbcan API handle
typedef long long dev_hdl;///< generic device handle


//===========================================================================
//                             INITIALIZATION
//
/// \addtogroup lcb_init Initialisation
/// Initialize communication to device.
/// This group defines all required functions for initialisation of a
/// proper communication to the device.
/// \{
//===========================================================================
//---------------------------------------------------------------------------
/// Initialize LabCanBus instance.
/// Initializes resources for a LabCanBus instance, connects to LabCanBus
/// and scans for connected devices.
/// \param[in] pDeviceConfigPath Absolute path to the folder that contains
///            the device configuration files (XML config files - see
/// \param[in] PluginSearchPath An additional search path, where the QmixSDK
///            searches for device plugins. Normally the SDK searches in the
///            plugins/labbcan folder that is a direct child of your application
///            folder. If your plugins folder is located on a different location,
///            then you should provide a valid path here.
/// See \ref ConfigFiles for a detailed description of device configuration.
/// \retval ERR_NOERR indicates success
/// \retval -ERR_NOTDIR if the given config path is not a directory
/// \retval -ERR_NOENT if no device_properties.xml file exists in the given
///          device configuration directory
///
LCB_Func long LCB_CALL LCB_Open(const char* pDeviceConfigPath, const char*
	PluginSearchPath);


//---------------------------------------------------------------------------
/// Start network communication.
/// This function sets all connected devices into state operational and
/// enabled. After a call to this function it is possible to access the
/// connected devices.
/// \return Error code - ERR_NOERR indicates success
///
LCB_Func long LCB_CALL LCB_Start();


//---------------------------------------------------------------------------
/// Stop network communication.
/// This function stops network communication and closes the CAN device
/// driver. The function should be called by application before LCB_Close();
/// \return Error code - ERR_NOERR indicates success
///
LCB_Func long LCB_CALL LCB_Stop();


//---------------------------------------------------------------------------
/// Close LabCanBus instance.
/// This call deletes all internal data structures and frees all allocated
/// resources
/// \return Error code - ERR_NOERR indicates success
///
LCB_Func long LCB_CALL LCB_Close();


//---------------------------------------------------------------------------
/// Write one message into log file.
/// \param[in] pLogMsg Message to write into log file
/// \return Error code - ERR_NOERR indicates success
///
LCB_Func long LCB_CALL LCB_Log(const char *pLogMsg);
/// \} lcb_init


//===========================================================================
//                             ERROR / EVENT HANDLING
//
/// \addtogroup lcb_error Error and Event Handling
/// Error and event handling
/// This group defines all required functions for handling of common bus
/// events and errors.
/// \{
//===========================================================================

//---------------------------------------------------------------------------
/// Get descriptive error message for a certain error return code.
/// \param[in]  ErrCode  Error code of device error that occurred
/// \param[out] pMsgBuf  Message buffer for storage of error message string
/// \param[in]  MsgBufSize Size of message buffer pMsgBuf in bytes
/// \return Error code - ERR_NOERR indicates success
///
LCB_Func long LCB_CALL LCB_GetErrMsg(long    ErrCode,
                                      char   *pMsgBuf,
                                      int     MsgBufSize);

/**
 * If an error occurs, then a function returns an error code.
 * This error code can be converted into an error message.
 * For many errors additional extended error information is stored internally.
 * So in case a function returns an error, you can call this function
 * Immediately to get optional extended error information.
 * \param[out] pStringBuf  Message buffer for storage of error message string
 * \param[in]  StringBufSize Size of message buffer pMsgBuf in bytes
 * \return Error code - ERR_NOERR indicates success
 */
LCB_Func long LCB_CALL LCB_GetExtendedLastErrorString(char *pStringBuf,
                                                      int StringBufSize);


//--------------------------------------------------------------------------
/// Try to read one event from the lab event queue.
/// The internal queue stores events like network events, emergency events
/// of single devices. This function tries to read one event from this queue
/// and returns immediately with -ERR_AGAIN if no event is in queue.
/// \param[out] pEventId Stores the event identifier read from queue
/// \param[out] pData1   Stores the event specific data 1
/// \param[out] pData2   Stores the event specific data 2
/// \param[out] pData3   Stores the event specific data 3
///
/// \retval  ERR_NOERR  A event has been read successfully from queue
/// \retval  ERR_AGAIN  The queue is empty - try again later
/// \retval  ERR_PARAM_INVALID The bus handle in hBus is not valid or initialized
/// \see lcb_event_id
/// \deprecated This function is deprecated. Use LCB_ReadEventEx() for future
///             implementations
///
LCB_Func long LCB_CALL LCB_ReadEvent(long   *pEventId,
                                     long   *pData1,
                                     long   *pData2,
                                     long   *pData3);


//--------------------------------------------------------------------------
/// Try to read one event from the lab event queue.
/// The internal queue stores events like network events, emergency events,
/// data link layer events or events of single devices. This function tries to
/// read one event from this queue and returns immediately with -ERR_AGAIN if
/// no event is in queue.
/// \param[out] pEventId Stores the event identifier read from queue. See
///             \ref LCB_EventId for a detailed description of the event identifiers.
/// \param[out] pDeviceHandle Returns a device handle for certain event types
/// \param[out] pData1 Stores the event specific data 1
/// \param[out] pData2 Stores the event specific data 2
/// \param[out] pEventString Returns a descriptive string of the event and its
///             parameters.
/// \param[in] EventStringSize Size of the message buffer for the returned
///            string
///
/// \retval  ERR_NOERR  A event has been read successfully from queue
/// \retval  ERR_AGAIN  The queue is empty - try again later
/// \retval  ERR_PARAM_INVALID The bus handle in hBus is not valid or initialized
/// \see LCB_EventId and LCB_GuardEventId
///
LCB_Func long LCB_CALL LCB_ReadEventEx(long    *pEventId,
                                       dev_hdl *pDeviceHandle,
                                       long *pData1,
                                       long *pData2,
                                       char *pEventString,
                                       int EventStringSize);
/// \} lcb_error




//===========================================================================
//                         DEVICE SPECIFIC FUNCTIONS
//
/// \addtogroup lcb_device Device Management
/// Common labCAN bus device handling and management
/// This group defines all common functions for handling of devices attached
/// to labCAN bus.
/// \{
//===========================================================================

//--------------------------------------------------------------------------
/// Read last device error from a specific device.
/// If an error occured then the device stores the last error so that
/// it is accessible later at any time. This function reads the last error
/// code from the device. Call LCB_GetDevErrMsg() to get a more descriptive
/// error message for a certain device error code.
/// \param[in]  DeviceHandle    Valid device handle
/// \param[out] pDevErr Returns last device error
/// \return Error code - ERR_NOERR indicates success
///
LCB_Func long LCB_CALL LCB_ReadLastDevErr(dev_hdl        DeviceHandle,
                                           unsigned long *pDevErr);


//--------------------------------------------------------------------------
/// Get the error string for a certain device error message.
/// This function decodes the error code obtained by a call to
/// LCB_ReadLastDevErr().
/// \param[in]  DeviceHandle       Valid bus handle
/// \param[in]  DevErr     Device erorr code returned by readLastDevErr()
/// \param[out] pMsgBuf    Message buffer for storage of error message string
/// \param[in]  MsgBufSize Size of message buffer pMsgBuf in bytes
///
/// \retval  ERR_NOTSUP The erro code is unknown - no message was found
/// \retval  ERR_PARAM_INVALID Invalid device handle
/// \retval  ERR_NOERR Error message was found
///
LCB_Func long LCB_CALL LCB_GetDevErrMsg(dev_hdl        DeviceHandle,
                                         unsigned long  DevErr,
                                         char          *pMsgBuf,
                                         int            MsgBufSize);


//--------------------------------------------------------------------------
/// Query name of specific device.
/// Normally all devices are named. That means each device carries a unique
/// name
/// \param[in]  DeviceHandle           Valid device handle
/// \param[out] pNameStringBuf Message buffer for storage of error message string
/// \param[in]  StringBufSize  Size of message buffer pMsgBuf in bytes
/// \return Error code - ERR_NOERR indicates success
///
LCB_Func long LCB_CALL LCB_GetDevName(dev_hdl  DeviceHandle,
                                       char    *pNameStringBuf,
                                       int      StringBufSize);


//---------------------------------------------------------------------------
/// Read certain parameter from device.
/// Each device may contain a number of parameters to read or write.
/// These parameters are device specific and you need a good knowledge
/// or a good documentation of the device parameters.
/// \param[in]  DeviceHandle      Valid device handle
/// \param[in]  DevParamId   Device parameter identifier
/// \param[out] pReadBuf     Stores the data read from device
/// \param[in]  BufSize      Contains the size of the buffer
/// \param[in]  AdjustEndian This parameter indicates if the function should
///             adjust the endianess of the data read from device
///             If the device bus transports the data in
///             a different endian format like the host machine,
///             then the endianess will be adjusted if this parameter
///             is true. Normally this parameter should be set to true
///             for numbers (integers, bytes...) and to false for string
///             or other data.
/// \return     Error code - ERR_NOERR indicates success
/// \see LCB_WriteDevParam()
///
LCB_Func long LCB_CALL LCB_ReadDevParam(dev_hdl        DeviceHandle,
                                         unsigned long  DevParamId,
                                         void          *pReadBuf,
                                         unsigned long  BufSize,
                                         unsigned char  AdjustEndian);


//---------------------------------------------------------------------------
/// Write certain parameter to device.
/// See readDevParam for a detailed description
/// \param[in]  DeviceHandle      Valid device handle
/// \param[in]  DevParamId   Device parameter identifier
/// \param[out] pWriteBuf    Stores the data read from device
/// \param[in]  BufSize      Contains the size of the buffer and returns
///                          the numer of bytes read from device
/// \param[in]  AdjustEndian This parameter indicates if the function should
///             adjust the endianess of the data before writing to device
/// \return     Error code - ERR_NOERR indicates success
/// \see LCB_ReadDevParam()
/// \note For some parameters it might be necessary to set the device
///       communication state machine into a configurable state.
///
LCB_Func long LCB_CALL LCB_WriteDevParam(dev_hdl        DeviceHandle,
                                          unsigned long  DevParamId,
                                          void          *pWriteBuf,
                                          unsigned long  BufSize,
                                          unsigned char  AdjustEndian);


//---------------------------------------------------------------------------
/// Set device in a configurable state.
/// Some device parameters are only writeable if the device is not
/// operational but in a configurable state. The function LCB_WriteDevParam()
/// might require to set the device into an configurable state.
/// To set the device into a configurable state, this function should
/// be called with the parameter \ref LCB_COMM_CONFIGURABLE. If the configuration
/// is finished, the device should be set operational again by calling
/// this function with the parameter \ref LCB_COMM_OPERATIONAL.
/// \param[in]  DeviceHandle      Valid device handle
/// \param[in]  CommState    The communication state to set this device to
///                          - \ref LCB_COMM_STOPPED
///                          - \ref LCB_COMM_CONFIGURABLE
///                          - \ref LCB_COMM_OPERATIONAL
/// \return Error code - ERR_NOERR indicates success
/// \see LCB_CommState
///
LCB_Func long LCB_CALL LCB_SetCommState(dev_hdl       DeviceHandle,
                                         unsigned char CommState);


//---------------------------------------------------------------------------
/// Query node identifier of specific device
/// Each CANopen device has a unique node identifier that identifies the
/// device on a CAN bus.
/// \param[in]  DeviceHandle      Valid device handle
/// \retval >= 0 Node ID
/// \retval < 0 Error code
///
LCB_Func long LCB_CALL LCB_GetNodeId(dev_hdl DeviceHandle);


/**
 * Function for setting a device specific property.
 * Devices may support special device properties that are not accessible
 * via the common device specific API. Use this function to set the value
 * of a certain property by providing a property ID and a value.
 * @see LCB_GetDeviceProperty
 * @param[in] DeviceHandle Valid device handle
 * @param[in] PropertyId Device specific device property identifier
 * @param[in] Value Value to set for the given device property
 * @retval ERR_NOERR Success
 * @retval -ERR_NOTSUP The given device property is not supported for the
 *         device given in DeviceHandle
 * @retval < 0 Error code
 */
LCB_Func long LCB_CALL LCB_SetDeviceProperty(dev_hdl DeviceHandle,
	int PropertyId, double Value);


/**
 * Function for reading a device specific property.
 * @see LCB_SetDeviceProperty
 * @param[in] DeviceHandle Valid device handle
 * @param[in] PropertyId Device specific device property identifier
 * @param[out] Value Returns the current value of the given device property.
 * @retval ERR_NOERR Success
 * @retval -ERR_NOTSUP The given device property is not supported for the
 *         device given in DeviceHandle
 * @retval < 0 Error code
 */
LCB_Func long LCB_CALL LCB_GetDeviceProperty(dev_hdl DeviceHandle,
	int PropertyId, double* Value);

/**
 * Checks if the given DeviceHandle is a simulated device
 * @param[in] DeviceHandle Valid device handle
 * @retval 0 It is a real device
 * @retval 1 It is a simulated device
 * @retval < 0 Error code
 */
LCB_Func long LCB_CALL LCB_IsSimulated(dev_hdl DeviceHandle);
/// \} lcb_device


//===========================================================================
//                           UTILITY FUNCTIONS
//
/// \addtogroup lcb_utility Utility Functions
/// Common utility and helper functions.
/// This group defines a set of common support and helper functions.
/// \{
//===========================================================================

//---------------------------------------------------------------------------
/// Converts splitted time parameters into a C like time value
/// \param[in] Year Year i.e. 2009
/// \param[in] Month The month from 1 - 12
/// \param[in] Day   Day of month from 1 - 31
/// \param[in] Hour  Hour of day 0 - 23
/// \param[in] Minute Minute of hour from 0 - 59
/// \param[in] Second Second of minute from 0 - 59
/// \param[out] pTime Returns converted time value
/// \note Some functions require a time value. You can create this time value
///       by calling this function
/// \return Error code - ERR_NOERR indicates success
///
LCB_Func long LCB_CALL LCB_MakeTime(unsigned short Year,
                                     unsigned char  Month,
                                     unsigned short Day,
                                     unsigned char  Hour,
                                     unsigned char  Minute,
                                     unsigned char  Second,
                                     unsigned long *pTime);


//---------------------------------------------------------------------------
/// Splits a time value into its single components
/// \param[in]  Time The time value to be converted
/// \param[out] pYear Year i.e. 2009
/// \param[out] pMonth The month from 1 - 12
/// \param[out] pDay   Day of month from 1 - 31
/// \param[out] pHour  Hour of day 0 - 23
/// \param[out] pMinute Minute of hour from 0 - 59
/// \param[out] pSecond Second of minute from 0 - 59
/// \note Some functions retrun a time value. You can split this value into
///       single components with this function
/// \return Error code - ERR_NOERR indicates success
///
LCB_Func long LCB_CALL LCB_SplitTime(unsigned long   Time,
                                      unsigned short *pYear,
                                      unsigned char  *pMonth,
                                      unsigned short *pDay,
                                      unsigned char  *pHour,
                                      unsigned char  *pMinute,
                                      unsigned char  *pSecond);


//---------------------------------------------------------------------------
/// Returns the current local system time as a C like time type
/// \param[out] pTime The current local system time
/// \return Error code - ERR_NOERR indicates success
///
LCB_Func long LCB_CALL LCB_GetCurrentTime(unsigned long *pTime);


//---------------------------------------------------------------------------
/// Converts a time value into a string YYYY-MM-DD HH:mm:ss
/// \param[in] Time Time value \see  LCB_GetCurrentTime()
/// \param[out] pTimeStrBuf Time string buffer stores time string
/// \param[in]  BufSize Size of string buffer
/// \return Error code - ERR_NOERR indicates success
///
LCB_Func long LCB_CALL LCB_TimeToStr(unsigned long   Time,
                                      char           *pTimeStrBuf,
                                      unsigned char   BufSize);
/// \} lcb_utility
/// \} lcb_api


//---------------------------------------------------------------------------
#endif // labbCAN_Bus_APIH

