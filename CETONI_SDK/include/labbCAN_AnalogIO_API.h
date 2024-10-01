#ifndef labbCAN_AnalogIO_APIH
#define labbCAN_AnalogIO_APIH
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
/// \file     labbCAN_AnalogIO_API.h
/// \author   Uwe Kindler (UK)
/// \date     2007/07/23
/// \brief    labbCAN Analog I/O application programming interface
//
//===========================================================================

/**
 * \page AnalogIO_API Analog I/O Library
 * \ifnot bootstrap
 *    \tableofcontents
 *    <img src="Slider_AnalogIO_API_color.jpg" align="center" style="padding-right: 10px; width: 800px;">
 * \else
 *    \image html Slider_AnalogIO_API_color.jpg
 * \endif
 * \section AnalogIO_Introduction Introduction
 * This analog I/O library defines a common interface for reading analog input
 * values and writing analog output values.
 *
 * ---
 *
 * \section AnalogIO_Including Including
 * The way how you include the library functions in your own windows program,
 * depends on the compiler and on the programming language you use. In order to
 * access the analog I/O API, you have to include the library
 * **labbCAN_AnalogIO_API.dll** to your programming environment. You have
 * to copy this file to the working directory of your system or to the
 * application directory that contains your application EXE file.
 * Use the calling convention \b __stdcall for this library. This convention
 * is managing how the parameters are put on the stack and who is responsible
 * to clean the stack after the function execution.
 *
 * The interface of the library, constant definitions and declarations of the
 * library functions, is defined in the header file
 * \link labbCAN_AnalogIO_API.h interface/labbCAN_AnalogIO_API.h \endlink
 *
 * ---
 *
 * \section AnalogIO_Usage Analog I/O API Usage
 * \subsection AnalogIO_Step1 Retrieve device handle
 * To work with an analog I/O channel, you need a valid channel handle.
 * A channel handle is simply an opaque pointer to the internal channel object
 * created by the labbCAN environment. So the first thing you need do to is
 * obtaining a valid analog I/O channel handle.
 *
 * You can get a valid output channel handle with the function
 * LCAIO_LookupOutChanByName() and a valid input channel handle with
 * the function LCAIO_LookupInChanByName():
 * \code
 * dev_hdl hAnalogIn;
 * Result = LCAIO_LookupInChanByName("neMAXYS1_AnIN2", &hAnalogIn);
 * dev_hdl hAnalogOut;
 * Result = LCAIO_LookupOutChanByName("neMESYS_AnOUT1", &hAnalogOut);
 * \endcode
 *
 * \note You can get the channel names from the device configuration files (see
 * \ref ConfigFiles). Simply search in the channel list for *Lcl::CAnalogInChannel*
 * or *Lcl::CAnalogOutChannel* channels.
 *
 * \code
 * </ChannelList>
 *     <Channel Name="neMAXYS1_AnIN1">
			<Type>Lcl::CAnalogInChannel</Type>
			<Device>neMAXYS1_YAnalogIn</Device>
			<ChannelNo>0</ChannelNo>
			<Scaling Factor="1" Offset="0"/>
	    </Channel>
		<Channel Name="neMAXYS1_AnIN2">
			<Type>Lcl::CAnalogInChannel</Type>
			<Device>neMAXYS1_YAnalogIn</Device>
			<ChannelNo>1</ChannelNo>
			<Scaling Factor="1" Offset="0"/>
		</Channel>
 * </ChannelList>
 * \endcode
 *
 * \subsection AnalogIO_Reference Reference
 * See the \ref lcaio_api module for a detailed reference of all analog I/O
 * control, status and configuration functions.
 *
 * ---
 *
 * \section AnalogIO_ProgrammingInterface Programming Interface - API
 * See the \ref lcaio_api module for a detailed reference of
 * the Analog I/O library application programming interface
 */


/**
 *  \addtogroup lcaio_api labbCAN Analog I/O API
 *  \brief Analog I/O specific functions.
 *
 *  <img src="MenuItem_Analog_Library.png" align="left" style="padding-right: 10px;">
 *  This module defines all labbCAN analog I/O specific functions, identifiers
 *  and data types for controlloing analog I/O modules attached to the labbCAN
 *  bus. Analog modules are used for measurement of analog input signals or
 *  for generation of analog output signals. This module offers a device
 *  independent API for access to all supported labbCAN analog devices.
 *  \see See \ref AnalogIO_API for a detailed introduction and general overview of
 *  analog I/O library.
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
#ifndef LCAIO_Func
	#define LCAIO_Func QMIXSDK_EXTERNC QMIXSDK_DLLIMPORT
#endif
#define LCAIO_CALLBACK QMIXSDK_CALLBACK
#define LCAIO_CALL QMIXSDK_CALL
/// \endcond



//===========================================================================
//                     ANALOG IO CHANNEL INITIALISATION
//
/// \addtogroup lcaio_chan_init Channel Initialisation
/// Analog I/O module channel initialisation functions
/// This group defines all functions to initialise analog I/O
/// channels properly.
/// \{
//===========================================================================

//---------------------------------------------------------------------------
/// Query number of available analog output channels
/// \retval >= 0 Number of available analog output channels
/// \retval < 0  Error code
///
LCAIO_Func long LCAIO_CALL LCAIO_GetNoOfOutputChannels();


//---------------------------------------------------------------------------
/// Lookup for an analog output channel by its name.
/// \param[in] pChannelName The name to assign with this channel
/// \param[out] pOutChanHdl Handle to output channel handle if the channel
///                         was sucessfully opened
/// \retval -ERR_NODEV No device with the given name found
/// \retval ERR_NOERR indicates success
///
LCAIO_Func long LCAIO_CALL LCAIO_LookupOutChanByName(const char* pChannelName,
                                                    dev_hdl  *pOutChanHdl);


//---------------------------------------------------------------------------
/// Get analog out channel handle by its index.
/// \param[in] Index Index into list of available analog out channels
/// \param[out] pOutChanHdl Handle to output channel or 0 if the given index is
///             out of range
/// \retval -ERR_PARAM_RANGE If the given device index is out of range
/// \retval ERR_NOERR indicates success
///
LCAIO_Func long LCAIO_CALL LCAIO_GetOutChanHandle(unsigned char Index,
	dev_hdl* pOutChanHdl);


//---------------------------------------------------------------------------
/// Query number of available analog input channels
/// \retval >= 0 Number of available analog input channels
/// \retval < 0  Error code
///
LCAIO_Func long LCAIO_CALL LCAIO_GetNoOfInputChannels();


//---------------------------------------------------------------------------
/// Lookup for an analog input channel by its name.
/// \param[in] pChannelName The name to assign with this channel
/// \param[out] pInChanHdl Handle to input channel handle if the channel
///                         was sucessfully opened
/// \retval -ERR_NODEV No device with the given name found
/// \retval ERR_NOERR indicates success
///
LCAIO_Func long LCAIO_CALL LCAIO_LookupInChanByName(const char* pChannelName,
                                                   dev_hdl  *pInChanHdl);


//---------------------------------------------------------------------------
/// Get analog input channel handle by its index.
/// \param[in] Index Index into list of available analog input channels
/// \param[out] pInChanHdl Handle to input channel or 0 if the given index is
///             out of range
/// \retval -ERR_PARAM_RANGE If the given device index is out of range
/// \retval ERR_NOERR indicates success
///
LCAIO_Func long LCAIO_CALL LCAIO_GetInChanHandle(unsigned char Index,
	dev_hdl* pInChanHdl);
/// \} lcaio_chan_init


//===========================================================================
//                     ANALOG OUT CHANNEL ACCESS
//
/// \addtogroup lcaio_out Analog Output
/// Analog output channel functions
/// This group defines all functions to output analog signals on specific
/// channels.
/// \{
//===========================================================================

//---------------------------------------------------------------------------
/// Set analog output value of single channel.
/// \param[in]  OutChanHdl Handle to analog output channel
/// \param[in]  fValue The anlog output value to set
/// \return Error code - ERR_NOERR indicates success
///
LCAIO_Func long LCAIO_CALL LCAIO_WriteOutput(dev_hdl OutChanHdl, double fValue);


//---------------------------------------------------------------------------
/// Return the output value of this channel.
/// \param[in]  OutChanHdl Handle to analog output channel
/// \param[in]  pfValue Returns the actual set output value
/// \return Error code - ERR_NOERR indicates success
///
LCAIO_Func long LCAIO_CALL LCAIO_GetOutputValue(dev_hdl OutChanHdl, double *pfValue);


//---------------------------------------------------------------------------
/// Enable / disable software scaling.
/// \param[in]  OutChanHdl Handle to analog output channel
/// \param[in] ScalingOn 1 = Scaling on, 0 = Scaling off
/// \return Error code - ERR_NOERR indicates success
///
LCAIO_Func long LCAIO_CALL LCAIO_SetOutputSwScalingOn(dev_hdl     OutChanHdl,
                                                     int ScalingOn);


//---------------------------------------------------------------------------
/// Set software scaling parameters.
/// These parameters are used to scale the measured value from device.
/// These scaling parameters are independent from the device scaling
/// parameters and the scaling is performed on the local machine.
/// Scaled Value = (Process Value * Scaling Factor) + Scaling Offset.
/// The default value for Scaling Factor is 1 and for Scaling Offset is 0.
/// \param[in]  OutChanHdl Handle to analog output channel
/// \param[in] ScalingFactor The scaling factor to multiply with field value
/// \param[in] ScalingOffset The scaling offset ro add to field value
/// \retval ERR_NOERR indicates success
/// \retval -ERR_NOTSUP Setting linear scaling parameters not supported (i.e.
///          if channel uses a different kind of scaling like PT100 scaling)
/// \see LCAIO_GetOutputSwScalingParam(), LCAIO_SetOutputSwScalingOn()
///
LCAIO_Func long LCAIO_CALL LCAIO_SetOutputSwScalingParam(dev_hdl OutChanHdl,
                                                        double    ScalingFactor,
                                                        double    ScalingOffset);


//---------------------------------------------------------------------------
/// Query software scaling parameters.
/// \param[in]  OutChanHdl Handle to analog output channel
/// \param[out] pScalingFactor The scaling factor multiplied with field value
/// \param[out] pScalingOffset The scaling offset added to field value
/// \retval ERR_NOERR indicates success
/// \retval -ERR_NOTSUP Linear scaling not supported (i.e.
///          if channel uses a different kind of scaling like PT100 scaling)
/// \see LCAIO_SetOutputSwScalingParam(), LCAIO_SetOutputSwScalingOn()
///
LCAIO_Func long LCAIO_CALL LCAIO_GetOutputSwScalingParam(dev_hdl  OutChanHdl,
                                                        double    *pScalingFactor,
                                                        double    *pScalingOffset);
/// \} lcaio_out


//===========================================================================
//                         ANALOG IN CHANNEL ACCESS
//
/// \addtogroup lcaio_in Analog Input
/// Analog input channel functions
/// This group defines all functions to measure analog input signals via
/// various analog input channels.
/// \{
//===========================================================================

//---------------------------------------------------------------------------
/// Read analog input of this channel.
/// \param[in]  InChanHdl Valid handle of analog input channel
/// \param[out] pfValue Return analog input value
/// \return Error code - ERR_NOERR indicates success
///
///
LCAIO_Func long LCAIO_CALL LCAIO_ReadInput(dev_hdl InChanHdl, double *pfValue);


//---------------------------------------------------------------------------
/// Read additional status information from analog channel.
/// \param[in]  InChanHdl Valid handle of analog input channel
/// \param[out] pdwStatus Returns the status read from the channel
/// \return Error code - ERR_NOERR indicates success
///
///
LCAIO_Func long LCAIO_CALL LCAIO_ReadStatus(dev_hdl InChanHdl, unsigned long *pdwStatus);


//---------------------------------------------------------------------------
/// Enable / disable software scaling.
/// \param[in]  InChanHdl Valid handle of analog input channel
/// \param[in] ScalingOn 1 = Scaling on, 0 = Scaling off
/// \return Error code - ERR_NOERR indicates success
///
LCAIO_Func long LCAIO_CALL LCAIO_SetInputSwScalingOn(dev_hdl     InChanHdl,
                                                    int ScalingOn);


//---------------------------------------------------------------------------
/// Set software scaling parameters.
/// These parameters are used to scale the measured value from device.
/// These scaling parameters are independent from the device scaling
/// parameters and the scaling is performed on the local machine.
/// Scaled Value = (Process Value * Scaling Factor) + Scaling Offset.
/// The default value for Scaling Factor is 1 and for Scaling Offset is 0.
/// \param[in]  InChanHdl Valid handle of analog input channel
/// \param[in] ScalingFactor The scaling factor to multiply with field value
/// \param[in] ScalingOffset The scaling offset ro add to field value
/// \retval ERR_NOERR indicates success
/// \retval -ERR_NOTSUP Linear scaling not supported (i.e.
///          if channel uses a different kind of scaling like PT100 scaling)
/// \see LCAIO_GetInputSwScalingParam(), LCAIO_SetInputSwScalingOn()
///
LCAIO_Func long LCAIO_CALL LCAIO_SetInputSwScalingParam(dev_hdl InChanHdl,
                                                       double    ScalingFactor,
                                                       double    ScalingOffset);


//---------------------------------------------------------------------------
/// Query software scaling parameters.
/// \param[in]  InChanHdl Valid handle of analog input channel
/// \param[out] pScalingFactor The scaling factor multiplied with field value
/// \param[out] pScalingOffset The scaling offset added to field value
/// \retval ERR_NOERR indicates success
/// \retval -ERR_NOTSUP Linear scaling not supported (i.e.
///          if channel uses a different kind of scaling like PT100 scaling)
/// \see LCAIO_SetInputSwScalingParam(), LCAIO_SetInputSwScalingOn()
///
LCAIO_Func long LCAIO_CALL LCAIO_GetInputSwScalingParam(dev_hdl InChanHdl,
                                                       double   *pScalingFactor,
                                                       double   *pScalingOffset);
/// \}


//===========================================================================
//                        COMMON CHANNEL FUNCTIONS
//
/// \addtogroup lcaio_common Common Channel Functions
/// Common channel specific auxiliary functions.
/// \{
//===========================================================================

//---------------------------------------------------------------------------
/// Query name of specific channel.
/// Normally all channels are named. That means each channel carries a
/// unique name
/// \param[in]  hChan           Valid input/outut channel handle
/// \param[out] pNameStringBuf  Message buffer for storage of error message string
/// \param[in]  StringBufSize   Size of buffer pNameStringBuf in bytes
/// \return Error code - - ERR_NOERR indicates success
///
LCAIO_Func long LCAIO_CALL LCAIO_GetChanName(dev_hdl  hChan,
                                            char      *pNameStringBuf,
                                            int        StringBufSize);


//---------------------------------------------------------------------------
/// Query analog I/O device of a certain analog I/O channel.
/// \param[in]  hChan               Valid input/outut channel handle
/// \param[out] pAnalogIoDeviceHdl  Handle of analog IO device
/// \return Error code - - ERR_NOERR indicates success
///
LCAIO_Func long LCAIO_CALL LCAIO_GetAnalogIoDevice(dev_hdl  hChan,
                                                  dev_hdl *pAnalogIoDeviceHdl);


//---------------------------------------------------------------------------
/// Lookup an analog I/O device by its name.
/// \param[in]  pName               Name of the device
/// \param[out] pAnalogIoDeviceHdl  Handle of analog IO device
/// \return Error code - - ERR_NOERR indicates success
///
LCAIO_Func long LCAIO_CALL LCAIO_LookupAnalogIoDeviceByName(char      *pName,
                                                           dev_hdl *pAnalogIoDeviceHdl);


/// \} lcaio_common
/// \} lcaio_api
//---------------------------------------------------------------------------
#endif // labbCAN_AnalogIO_APIH

