#ifndef labbCAN_Controller_APIH
#define labbCAN_Controller_APIH
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
/// \file     labbCAN_Controller_API.h
/// \author   Uwe Kindler (UK)
/// \date     2011/05/25
/// \brief    labbCAN Controller Application Programming Interface
//
//===========================================================================

/**
 * \page Controller_API Controller Library
 * \ifnot bootstrap
 *    \tableofcontents
 *    <img src="Slider_Controller_API_color.jpg" align="center" style="padding-right: 10px; width: 800px;">
 * \else
 *    \image html Slider_Controller_API_color.jpg
 * \endif
 * \section Controller_Introduction Introduction
 * This controller library defines a common interface for control device
 * access and configuration.
 *
 * ---
 *
 * \section Controller_Including Including
 * The way how you include the library functions in your own windows program,
 * depends on the compiler and on the programming language you use. In order to
 * access the controller API, you have to include the library
 * **labbCAN_Controller_API.dll** to your programming environment. You have
 * to copy this file to the working directory of your system or to the
 * application directory that contains your application EXE file.
 * Use the calling convention \b LCC_CALL for this library. This convention
 * is managing how the parameters are put on the stack and who is responsible
 * to clean the stack after the function execution.
 *
 * The interface of the library, constant definitions and declarations of the
 * library functions, is defined in the header file
 * \link labbCAN_Controller_API.h interface/labbCAN_Controller_API.h \endlink
 *
 * ---
 *
 * \section Controller_API_Usage Controller API Usage
 * \subsection Controller_Step1 Retrieve device handle
 * To work with a controller channel, you need a valid channel handle.
 * A channel handle is simply an opaque pointer to the internal channel object
 * created by the labbCAN environment. So the first thing you need do to is
 * obtaining a valid control channel handle. There are two ways to get a valid
 * channel handle. The first method is to get a channel object via its channel
 * name.
 *
 * To do this, use the function LCC_LookupChanByName().
 * \code{.c}
 * dev_hdl ControlChannelHandle;
 * Result = LCC_LookupChanByName("QmixTC_1_Ctrl1", &ControlChannelHandle);
 * \endcode
 *
 * You can get the channel names from the device configuration files (see
 * \ref ConfigFiles). To search for the control channel names, open the file
 * **qmixcontroller.xml** and search in the channel list for
 * **Lcl::CLocalControllerChannel** items. The following example shows the
 * device configuration of one single Qmix TC control channel. In the first
 * line you will find the channel name - **QmixTC_1_Ctrl1** in this case.
 *
 * \includelineno controller_devicename.xml
 *
 * The second method is, to get the channel name by its index. All control
 * channels are number from 0 to n-1 channels. To get a channel by its index,
 * use the function LCC_GetChannelHandle().
 * \code{.c}
 * dev_hdl ControlChannelHandle;
 * Result = LCC_GetChannelHandle(0, &ControlChannelHandle);
 * \endcode
 *
 * If you want to know, how many channels are available, simply call
 * the function LCC_GetNoOfControlChannels(). The following example shows
 * how to use both functions to enumerate all control channels and output
 * their names.
 *
 * \includelineno ControlChannelEnumeration.cpp
 *
 * \subsection Controller_Usage Using Controller Channels
 * To use the control channel, you simply need to write a setpoint and enable
 * the channel control loop.
 * \code{.c}
 * Result = LCC_WriteSetPoint(ChannelHandle, 37);
 * Result = LCC_EnableControlLoop(ChannelHandle, 1);
 * \endcode
 *
 * Now you can use the function LCC_ReadActualValue() to read the actual
 * control channel value. The following example shows the minimum number
 * of steps to get a control channel running.
 *
 * \includelineno Control_CAPI_Usage.cpp
 *
 * \subsection Controller_Reference Reference
 * See the \ref lcctrl_api module for a detailed reference of all controller
 * control, status and configuration functions.
 *
 * \section Controller_Dynamically Dynamically created control channels
 * The controller library supports the creation of dynamic control channels.
 * A dynamic control channel is a control channel, where the control loop input,
 * control loop output and the controller PID parameters are provided in source
 * code.
 * This enables the dynamic creation of special control loops and thus enables
 * things like pressure controlled dosage with syringe pumps. Dynamic
 * control channels are created with the function LCC_CreatePIDControlChannel().
 * The following code shows how to create a pressure control loop with an
 * analog input channel that measures the pressure and a syringe pump that
 * generates the flow and the pressure.
 *
 * \code{.c}
    dev_hdl ControlLoopIn;
    dev_hdl Pump;
    dev_hdl ControlChannel;

    LCAIO_GetInChanHandle(0, &ControlLoopIn);
    LCP_GetPumpHandle(0, &Pump);
    LCC_CreatePIDControlChannel(ControlLoopIn, Pump, PUMP_FLOW, &ControlChannel);
 * \endcode
 *
 * To build the control loop you need the device handles for the control loop
 * input and the control loop output. Then you can call the function
 * LCC_CreatePIDControlChannel() to wire input and output together to build
 * up a control loop.
 *
 * ---
 *
 * \section  Controller_ProgrammingInterface Programming Interface - API
 * See the \ref lcctrl_api module for a detailed reference of
 * the Controller I/O library application programming interface
 *
 * \example capi_dynamic_controller_test.cpp Dynamic heating control
 * The following sample shows how to combine an analog input channel and an
 * analog output channels to realize a heating control loop.
 *
 * \example capi_pressure_control_test.cpp Pressure control loop
 * The following example shows how to combine a analog input for pressure
 * measurement and a syringe pump for flow generation to build up a pressure
 * control loop for pressure controlled dosage.
 *
 * \example capi_qmixqplus_test.cpp
 * The example shows the minimum number of steps required to control a 
 * Qmix Q+ module.
 */

/**
 *  \addtogroup lcctrl_api labbCAN Controller API
 *  \brief Controller specific functions.
 *
 *  <img src="MenuItem_Controller_Library.png" align="left" style="padding-right: 10px;">
 *  This module defines all labbCAN controller specific functions, identifiers
 *  and data types for control of measurement and control devices attached
 *  to the labbCAN bus. Controller modules are used for closed loop control
 *  like heating, cooling or something else. The control is performed by an
 *  internal control algorithm like PID or Fuzzy control. The labbCAN
 *  controller module offers a device independent API for access to all
 *  supported labbCAN measurement and control devices.
 *  \see See \ref Controller_API for a detailed introduction and general
 *  overview of controller library.
 *
 *  <div style="padding: 20px;"></div>
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
#ifndef LCC_Func
	#define LCC_Func QMIXSDK_EXTERNC QMIXSDK_DLLIMPORT
#endif
#define LCC_CALLBACK QMIXSDK_CALLBACK
#define LCC_CALL QMIXSDK_CALL
/// \endcond

//---------------------------------------------------------------------------
/// Control loop output type
/// This enumeration defines the output types for dynamic control channels.
/// \see LCC_CreatePIDControlChannel
enum LoopOutType
{
	ANALOG,///< plain analog output channel that can output an analog value
	DIGITAL,///< digital output that can output 0 or 1 - e.g. to switch a heating on / off
	DIGITAL_PWM,///< uses a digital output to generate a PWM by switching the channel on / off
	PUMP_FLOW///< uses a pump a control loop output - e.g. for pressure controlled dosage
};


//---------------------------------------------------------------------------
/// ID parameter identifier
/// Identifier for all PID control loop parameter that can be changed via
/// LCC_SetPIDParameter. Before your can use a control loop, you should
/// properly set all control loop parameters. You can use the QmixElements
/// software for PID parameter testing and PID tuning.
/// \see LCC_CreatePIDControlChannel
enum PIDParameterId
{
	PID_PARAM_K = 0,///< proportional gain K
	PID_PARAM_T_I,///< integral time constant Ti
	PID_PARAM_T_D,///< differential time constant Td.
	PID_PARAM_DERIVATIVE_GAIN_LIMIT,///< the value the derivative gain is limited to. The derivative gain is computed from control loop error K and Td.
	PID_PARAM_T_T,///< value for dead time correction
	PID_PARAM_MAX_U,///< maximum control value
	PID_PARAM_MIN_U,///< minimum control value
	PID_PARAM_DISABLED_U,///< fixed control value that is set when the control loop is disabled.
	PID_PARAM_INITIAL_SETPOINT,///< the initial setpoint if no setpoint has been set (default 0)
	PID_PARAM_SAMPLE_TIME,///< sample time of pid control loop in milliseconds
	PID_PARAM_COUNT ///< this is just a delimter and not a real param
};


//===========================================================================
//                     CONTROLLER MODULE CONFIGURATION
//
/// \addtogroup lcctrl_chan_init Channel Initialisation
/// Controller module channel initialisation functions
/// This group defines all functions to initialise controller
/// channels properly. Each measurement and control device that is attached
/// to the labbCAN bus offers a number of controller channels.
/// \{
//===========================================================================

//---------------------------------------------------------------------------
/// Query number of available controller channels
/// \retval >= 0 Number of available control channels
/// \retval < 0  Error code
///
LCC_Func long LCC_CALL LCC_GetNoOfControlChannels();


//---------------------------------------------------------------------------
/// Lookup for a controller channel by its name.
/// \param[in] pChannelName The name to assign with this channel
/// \param[out] pChanHdl Handle to controller channel handle if the channel
///                      was sucessfully opened
/// \retval -ERR_NODEV No device with the given name found
/// \retval ERR_NOERR indicates success
/// \return Error code - ERR_NOERR indicates success
///
LCC_Func long LCC_CALL LCC_LookupChanByName(const char* pChannelName,
                                             dev_hdl*    pChanHdl);

//---------------------------------------------------------------------------
/// Get controller channel handle by its index.
/// \param[in] Index Index into list of available controller channels. The
///            index must be in the range of 0 - (LCC_GetNoOfControlChannels() - 1)
/// \param[out] pChanHdl Returns handle to control channel or 0 if the given
///             index is out of range
/// \retval -ERR_PARAM_RANGE If the given device index is out of range
/// \retval ERR_NOERR indicates success
///
LCC_Func long LCC_CALL LCC_GetChannelHandle(unsigned char Index,
	dev_hdl* pChanHdl);

/**
 * Function for creation of dynamic PID control channels.
 * With dynamic control channels you can create your own custom PID control
 * loops. You just need to provide an analog input channel that measures
 * the actual value and a control loop output for writing the control loop
 * output value. You can use analog /digital output channels and pumps as
 * control loop output. You can easily implement pressure controlled dosage
 * by combining an analog pressure sensor as control loop input and a syringe
 * pump as control loop output. The following example code shows how to
 * do this
 * \code{.c}
    dev_hdl ControlLoopIn;
    dev_hdl Pump;
    dev_hdl ControlChannel;

    LCAIO_GetInChanHandle(0, &ControlLoopIn);
    LCP_GetPumpHandle(0, &Pump);
    LCC_CreatePIDControlChannel(ControlLoopIn, Pump, PUMP_FLOW, &ControlChannel);
 * \endcode
 * If you have created a channel, you need to call LCC_SetPIDParameter() to
 * configure the PID parameters of the channel. If you have configured
 * the PID parameters properly, you can enable the control loop via
 * LCC_EnableControlLoop().
 * @param AnalogInput The control loop input - channel handle of an analog input device.
 * @param Output The control loop output - you can pass in an analog out channel
 *        a digital out channel or a pump device.
 * @param LoopOutType Provide the type of the loop output that should get created
 *        by this function. The type need to match the type passed in in
 *        Output parameter. The following types are supported:
 *        - ANALOG A simple analog output - e.g. for controlling a heater
 *        - DIGITAL A simple digital switch - e.g. for switching a heater
 *        - DIGITAL_PWM A loop output that uses a digital output channel to
 *          create a PWM  - e.g. for PWM control of a peltier element
 *        - PUMP_FLOW A loop output that controls the flow rate of a pump
 *        (see LoopOutType for all output type identifiers)
 * @param pCreatedChannel Returns the handle to controller channel handle if
 *        the channel was successfully created.
 * \see LoopOutType for an enumeration of all loop output types
 * \return Error code - ERR_NOERR indicates success
 */
LCC_Func long LCC_CALL LCC_CreatePIDControlChannel(dev_hdl AnalogInput, dev_hdl Output,
	unsigned int LoopOutType, dev_hdl* pCreatedChannel);
/// \} lcctrl_chan_init


//===========================================================================
//                     CONTROLLER CHANNEL ACCESS
//
/// \addtogroup lcctrl_chan_access Control Channel Access
/// Control channel access functions
/// This group defines all functions for access to control parameters like
/// setpoint or actual value
/// \{
//===========================================================================


/**
 * Set the PID parameters of a certain control channel.
 * \see PIDParameterId for a list of all available parameters.
 * If you create a dynamic control channel, the you need to set all PID
 * parameters before you enable the channel via LCC_EnableControlLoop().
 * @param ChanHdl Valid handle of a controller channel
 * @param PIDParamId PID parameter identifier - \see PIDParameterId for a list
 *        of all PID parameters
 * @param Value The value for the PID parameter given in PIDParamId
 * \return Error code - ERR_NOERR indicates success
 */
LCC_Func long LCC_CALL LCC_SetPIDParameter(dev_hdl ChanHdl, int PIDParamId,
	double Value);

/**
 * Enables / disables a control loop.
 * If the control loop is enabled, then the output value is calculated
 * periodically.
 * @param ChanHdl Valid handle of a controller channel
 * @param Enable 1 = enable, 0 = disable
 * \return Error code - ERR_NOERR indicates success
 * \see LCC_IsControlLoopEnabled()
 */
LCC_Func long LCC_CALL LCC_EnableControlLoop(dev_hdl ChanHdl, int Enable);


/**
 * Query if a control loop is enabled.
 * If the control loop is enabled, then the output value is calculated
 * periodically.
 * @param ChanHdl Valid handle of a controller channel
 * \retval 1 - Control channel is enabled
 * \retval 0 - Control channel is disabled
 * \retval <0 - Error code
 * \see LCC_EnableControlLoop()
 */
LCC_Func long LCC_CALL LCC_IsControlLoopEnabled(dev_hdl ChanHdl);


//---------------------------------------------------------------------------
/// Write setpoint value to controller device.
/// \param[in] ChanHdl  Valid handle of open controller channel
/// \param[in] fSetPointValue The setpoint value to write
/// \return Error code - ERR_NOERR indicates success
///
LCC_Func long LCC_CALL LCC_WriteSetPoint(dev_hdl ChanHdl, double fSetPointValue);


//--------------------------------------------------------------------------
/// Write setpoint value to controller device - bypass scaling stage.
/// \param[in] ChanHdl  Valid handle of open controller channel
/// \param[in] SetPointValueRaw Unprocessed set point value (no scaling)
/// \return Error code - ERR_NOERR indicates success
///
LCC_Func long LCC_CALL LCC_WriteSetPointUnscaled(dev_hdl ChanHdl, double SetPointValueRaw);


//---------------------------------------------------------------------------
/// Query setpoint value from device object.
/// This function does not return the real setpoint value of the device
/// but only the cached setpoint value entered by writeSetPoint()
/// \param[in] ChanHdl  Valid handle of open controller channel
/// \param[in] pfSetPointValue The setpoint value read from device
/// \return Error code - ERR_NOERR indicates success
///
LCC_Func long LCC_CALL LCC_GetSetPoint(dev_hdl ChanHdl, double *pfSetPointValue);


//---------------------------------------------------------------------------
/// Read actual value from device.
/// \param[in] ChanHdl  Valid handle of open controller channel
/// \param[out] pfActualValue Returns the actual controller value
/// \return Error code - ERR_NOERR indicates success
///
LCC_Func long LCC_CALL LCC_ReadActualValue(dev_hdl ChanHdl, double *pfActualValue);


//---------------------------------------------------------------------------
/// Read actual value from device - bypass scaling.
/// Reads the actual value from the device bypassing the scaling stage
/// of the channel. Reads the unprocessed value directly.
/// \param[in] ChanHdl  Valid handle of open controller channel
/// \param[out] pfActualValueRaw Unprocessed actual value (no scaling)
/// \return Error code - ERR_NOERR indicates success
///
LCC_Func long LCC_CALL LCC_ReadActualValueUnscaled(dev_hdl ChanHdl, double *pfActualValueRaw);


//---------------------------------------------------------------------------
/// Read additional status information from device.
/// \param[in] ChanHdl  Valid handle of open controller channel
/// \param[out] pdwStatus Stores the status read from device
/// \return Error code - ERR_NOERR indicates success
///
LCC_Func long LCC_CALL LCC_ReadStatus(dev_hdl ChanHdl, unsigned long *pdwStatus);


//---------------------------------------------------------------------------
/// Enable / disable software scaling.
/// \param[in]  ChanHdl  Valid handle of open controller channel
/// \param[in] ScalingOn 1 = Scaling on, 0 = Scaling off
/// \return Error code - ERR_NOERR indicates success
///
LCC_Func long LCC_CALL LCC_SetSwScalingOn(dev_hdl ChanHdl,
                                          int ScalingOn);


//---------------------------------------------------------------------------
/// Set software scaling parameters.
/// These parameters are used to scale the measured value from device.
/// These scaling parameters are independent from the device scaling
/// parameters and the scaling is performed on the local machine.
/// Scaled Value = (Process Value * Scaling Factor) + Scaling Offset.
/// The default value for Scaling Factor is 1 and for Scaling Offset is 0.
/// \param[in] ChanHdl  Valid handle of open controller channel
/// \param[in] fScalingFactor The scaling factor to multiply with field value
/// \param[in] fScalingOffset The scaling offset ro add to field value
/// \retval ERR_NOERR indicates success
/// \retval -ERR_NOTSUP Linear scaling not supported (i.e.
///          if channel uses a different kind of scaling like PT100 scaling)
/// \see LCC_GetSwScalingParam()
///
LCC_Func long LCC_CALL LCC_SetSwScalingParam(dev_hdl ChanHdl,
                                              double  fScalingFactor,
                                              double  fScalingOffset);


//---------------------------------------------------------------------------
/// Read software scaling parameters.
/// \param[in] ChanHdl  Valid handle of open controller channel
/// \param[out] pfScalingFactor The scaling factor multiplied with field value
/// \param[out] pfScalingOffset The scaling offset added to field value
/// \see LCC_SetSwScalingParam()
/// \retval ERR_NOERR indicates success
/// \retval -ERR_NOTSUP Linear scaling not supported (i.e.
///          if channel uses a different kind of scaling like PT100 scaling)
///
LCC_Func long LCC_CALL LCC_GetSwScalingParam(dev_hdl  ChanHdl,
                                              double  *pfScalingFactor,
                                              double  *pfScalingOffset);
/// \} lcctrl_chan_access


//===========================================================================
//                        COMMON CHANNEL FUNCTIONS
//
/// \addtogroup lcctrl_common Common Channel Functions
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
LCC_Func long LCC_CALL LCC_GetChanName(dev_hdl  hChan,
                                        char   *pNameStringBuf,
                                        int     StringBufSize);


//---------------------------------------------------------------------------
/// Lookup a controller device by its name.
/// \param[in]  pName           Name of the device
/// \param[out] pCtrlDeviceHdl  Handle of controller device
/// \return Error code - - ERR_NOERR indicates success
///
LCC_Func long LCC_CALL LCC_LookupCtrlDeviceByName(char    *pName,
                                                   dev_hdl *pCtrlDeviceHdl);
/// \} lcctrl_common
/// \} lcctrl_api
//---------------------------------------------------------------------------
#endif // labbCAN_Controller_APIH

