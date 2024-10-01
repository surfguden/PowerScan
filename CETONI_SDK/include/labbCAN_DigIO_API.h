#ifndef labbCAN_DigIO_APIH
#define labbCAN_DigIO_APIH
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
/// \file     labbCAN_DigIO_API.h
/// \author   Uwe Kindler (UK)
/// \date     2011/05/25
/// \brief    labbCan Digital I/O Application Programming Interface
//
//===========================================================================


/**
 * \page DigIO_API Digital I/O Library
 * \ifnot bootstrap
 *    \tableofcontents
 *    <img src="Slider_DigitalIO_API_color.jpg" align="center" style="padding-right: 10px; width: 800px;">
 * \else
 *    \image html Slider_DigitalIO_API_color.jpg
 * \endif
 * \section DigIO_Introduction Introduction
 * This digital I/O library defines a common interface for reading digital input
 * states and setting digital outputs.
 *
 * ---
 *
 * \section DigIO_Including Including
 * The way how you include the library functions in your own windows program,
 * depends on the compiler and on the programming language you use. In order to
 * access the digital I/O API, you have to include the library
 * **labbCAN_DigIO_API.dll** to your programming environment. You have
 * to copy this file to the working directory of your system or to the
 * application directory that contains your application EXE file.
 * Use the calling convention \b LCDIO_CALL for this library. This convention
 * is managing how the parameters are put on the stack and who is responsible
 * to clean the stack after the function execution.
 *
 * The interface of the library, constant definitions and declarations of the
 * library functions, is defined in the header file
 * \link labbCAN_DigIO_API.h interface/labbCAN_DigIO_API.h \endlink
 *
 * ---
 *
 * \section DigIO_Usage Digital I/O API Usage
 * \subsection DigIO_Step1 Retrieve device handle
 * To work with an digital I/O channel, you need a valid channel handle.
 * A channel handle is simply an opaque pointer to the internal channel object
 * created by the labbCAN environment. So the first thing you need do to is
 * obtaining a valid digital I/O channel handle.
 *
 * You can get a valid output channel handle with the function
 * LCDIO_LookupOutChanByName() and a valid input channel handle with
 * the function LCDIO_LookupInChanByName():
 * \code
 * dev_hdl DigInHandle;
 * Result = LCDIO_LookupInChanByName("neMAXYS1_DigIN2", &DigInHandle);
 * dev_hdl DigOutHandle;
 * Result = LCDIO_LookupOutChanByName("neMAXYS1_DigOUT3", &DigOutHandle);
 * \endcode
 *
 * \note You can get the channel names from the device configuration files (see
 * \ref ConfigFiles). Simply search in the channel list for *Lcl::CDigitalInChannel*
 * or *Lcl::CDigitalOutChannel* channels.
 *
 * \code
 * </ChannelList>
       <Channel Name="neMAXYS1_DigIN4">
           <Type>Lcl::CDigitalInChannel</Type>
           <Device>neMAXYS1_YDigitalIn</Device>
           <ChannelNo>12<!-- General purpose D --></ChannelNo>
       </Channel>
       <Channel Name="neMAXYS1_DigOUT1">
            <Type>Lcl::CDigitalOutChannel</Type>
            <Device>neMAXYS1_YDigitalOut</Device>
            <ChannelNo>15<!-- General purpose A --></ChannelNo>
       </Channel>
 * </ChannelList>
 * \endcode
 *
 * \subsection DigIO_Reference Reference
 * See the \ref lcdio_api module for a detailed reference of all digital I/O
 * control, status and configuration functions.
 *
 * ---
 *
 * \section  DigIO_ProgrammingInterface Programming Interface - API
 * See the \ref lcdio_api module for a detailed reference of
 * the Digital I/O library application programming interface
 */


/**
 *  \addtogroup lcdio_api labbCAN Digital I/O API
 *  \brief Digital I/O specific functions.
 *
 *  <img src="MenuItem_Digital_Library.png" align="left" style="padding-right: 10px;">
 *  This module defines all labbCAN digital I/O specific functions, identifiers
 *  and data types for controlling digital I/O modules attached to the labbCAN
 *  bus. Digital I/O modules are used for detection of digital input signals
 *  and for switching of digital output signals. This module offers a device
 *  independent API for access to all supported labbCAN digital devices.
 *  \see See \ref DigIO_API for a detailed introduction and general overview of
 *  digital I/O library.
 *
 *  <div style="padding: 30px;"></div>
 *  \{
 */


//===========================================================================
//                                 INCLUDES
//===========================================================================
#include "labbCAN_Bus_API.h"


//===========================================================================
//                                DEFINES
//===========================================================================
/// \cond private
#ifndef LCDIO_Func
	#define LCDIO_Func QMIXSDK_EXTERNC QMIXSDK_DLLIMPORT
#endif
#define LCDIO_CALLBACK QMIXSDK_CALLBACK
#define LCDIO_CALL QMIXSDK_CALL
/// \endcond


//===========================================================================
//                     DIGITAL IO MODULE CONFIGURATION
//
/// \addtogroup lcdio_chan_init Channel Initialisation
/// Digital I/O module channel initialisation functions
/// This group defines all functions to initialise digital I/O
/// channels properly. Each digital I/O device that is attached to the
/// labbCAN bus offers a number of digital channels.
/// \{
//===========================================================================

//---------------------------------------------------------------------------
/// Query number of available digital output channels
/// \retval >= 0 Number of available digital output channels
/// \retval < 0  Error code
///
LCDIO_Func long LCDIO_CALL LCDIO_GetNoOfOutputChannels();


//---------------------------------------------------------------------------
/// Lookup for an digital output channel by its name.
/// \param[in] pChannelName The name to assign with this channel
/// \param[out] pOutChanHdl Handle to output channel handle if the channel
///                         was successfully opened
/// \retval -ERR_NODEV No device with the given name found
/// \retval ERR_NOERR indicates success
///
LCDIO_Func long LCDIO_CALL LCDIO_LookupOutChanByName(const char* pChannelName,
                                                    dev_hdl *   pOutChanHdl);


//---------------------------------------------------------------------------
/// Get digital out channel handle by its index.
/// \param[in] Index Index into list of available digital out channels
/// \param[out] pOutChanHdl Handle to output channel or 0 if the given index is
///             out of range
/// \retval -ERR_PARAM_RANGE If the given device index is out of range
/// \retval ERR_NOERR indicates success
///
LCDIO_Func long LCDIO_CALL LCDIO_GetOutChanHandle(unsigned char Index,
	dev_hdl* pOutChanHdl);


//---------------------------------------------------------------------------
/// Query number of available digital input channels
/// \retval >= 0 Number of available digital input channels
/// \retval < 0  Error code
///
LCDIO_Func long LCDIO_CALL LCDIO_GetNoOfInputChannels();


//---------------------------------------------------------------------------
/// Lookup for a digital input channel by its name.
/// \param[in] pChannelName The name to assign with this channel
/// \param[out] pInChanHdl Handle to input channel handle if the channel
///                         was successfully opened
/// \retval -ERR_NODEV No device with the given name found
/// \retval ERR_NOERR indicates success
///
LCDIO_Func long LCDIO_CALL LCDIO_LookupInChanByName(const char* pChannelName,
                                                   dev_hdl*    pInChanHdl);


//---------------------------------------------------------------------------
/// Get digital input channel handle by its index.
/// \param[in] Index Index into list of available digital input channels
/// \param[out] pInChanHdl Handle to input channel or 0 if the given index is
///             out of range
/// \retval -ERR_PARAM_RANGE If the given device index is out of range
/// \retval ERR_NOERR indicates success
///
LCDIO_Func long LCDIO_CALL LCDIO_GetInChanHandle(unsigned char Index,
	dev_hdl* pInChanHdl);
/// \} lcdio_chan_init


//===========================================================================
//                     DIGITAL OUT CHANNEL ACCESS
//
/// \addtogroup lcdio_out Digital Output
/// Digital output channel functions
/// This group defines all functions to set digital output signals a certain
/// digital output channels.
/// \{
//===========================================================================

//---------------------------------------------------------------------------
/// Swicth digital output channel on/off.
/// \param[in]  OutChanHdl Handle to digital output channel
/// \param[in]  On  State to set 0 = switch off, 1 = switch on
/// \return Error code - ERR_NOERR indicates success
///
LCDIO_Func long LCDIO_CALL LCDIO_WriteOn(dev_hdl OutChanHdl, int On);


//---------------------------------------------------------------------------
/// Return the state of a digital output channel.
/// \param[in] OutChanHdl Handle to digital output channel
/// \retval 1 Channel is ON
/// \retval 0 Channel is OFF
/// \retval <0 Error code
///
LCDIO_Func long LCDIO_CALL LCDIO_IsOutputOn(dev_hdl OutChanHdl);
/// \} lcdio_out


//===========================================================================
//                     DIGITAL IN CHANNEL ACCESS
//
/// \addtogroup lcdio_in Digital Input
/// Digital input channel functions
/// This group defines all functions detect digital input signals on certain
/// digital input channels.
/// \{
//===========================================================================

//---------------------------------------------------------------------------
/// Read digital input state of channel.
/// \param[in]  InChanHdl Handle to digital input channel
/// \retval 1 Channel is ON
/// \retval 0 Channel is OFF
/// \retval <0 Error code
///
LCDIO_Func long LCDIO_CALL LCDIO_IsInputOn(dev_hdl InChanHdl);

/// \} lcdio_in


//===========================================================================
//                        COMMON CHANNEL FUNCTIONS
//
/// \addtogroup lcdio_common Common Channel Functions
/// Common channel specific auxiliary functions.
/// \{
//===========================================================================

//---------------------------------------------------------------------------
/// Query name of specific channel.
/// Normally all channels are named. That means each channel carries a
/// unique name
/// \param[in]  hChan           Valid input/output channel handle
/// \param[out] pNameStringBuf  Message buffer for storage of error message string
/// \param[in]  StringBufSize   Size of buffer pNameStringBuf in bytes
/// \return Error code - - ERR_NOERR indicates success
///
LCDIO_Func long LCDIO_CALL LCDIO_GetChanName(dev_hdl  hChan,
                                            char    *pNameStringBuf,
                                            int      StringBufSize);


//---------------------------------------------------------------------------
/// Lookup an analog I/O device by its name.
/// \param[in]  pName         Name of the device
/// \param[out] pIoDeviceHdl  Handle of a digital IO device
/// \return Error code - - ERR_NOERR indicates success
///
LCDIO_Func long LCDIO_CALL LCDIO_LookupIoDeviceByName(const char *pName,
                                                     dev_hdl    *pIoDeviceHdl);
/// \} lcdio_common
/// \} lcdio_api
//---------------------------------------------------------------------------
#endif // labbCAN_DigIO_APIH

