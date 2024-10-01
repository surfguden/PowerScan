#ifndef labbCAN_Pump_APIH
#define labbCAN_Pump_APIH
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
/// \file     labbCAN_Pump_API.h
/// \author   Uwe Kindler (UK)
/// \date     2012/07/13
/// \brief    labbCAN Pump Application Programming Interface
//
//===========================================================================

/**
 * \addtogroup lcp_api labbCAN Pump API
 * \brief Pump specific functions for various pump types.
 *
 * <img src="MenuItem_Pump_Library.png" align="left" style="padding-right: 10px;">
 * This module defines common labbCAN pump specific functions, identifiers
 * and data types for driving labbCAN conform pumps (syringe pumps, tubing pumps)
 * that are attached to a labbCAN software bus.
 *  \see See \ref PumpAPI for a detailed introduction and general overview of
 *  labbCAN pump library.
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
#ifndef LCP_Func
	#define LCP_Func QMIXSDK_EXTERNC QMIXSDK_DLLIMPORT
#endif
#define LCP_CALLBACK QMIXSDK_CALLBACK
#define LCP_CALL QMIXSDK_CALL
/// \endcond


/// \addtogroup lcp_pumpunits Pump SI units
/// Defines common SI units for volume and flow rate for all pump devices.
/// \{
//---------------------------------------------------------------------------
/// \addtogroup lcp_volunit Volume SI Units
/// Defines common volume SI units for all pump devices.
/// The units are based on the standardized CANopen unit system
/// \{
#define LITRES 68 //!< Litres
/// \} lcp_volunit


//---------------------------------------------------------------------------
/// \addtogroup lcp_forceunit Force SI Units
/// Defines common force SI units for all pump devices.
/// The units are based on the standardized CANopen unit system
/// \{
#define NEWTON 33 //!< Newton
/// \} lcp_forceunit


//---------------------------------------------------------------------------
/// \addtogroup lcp_prefix Prefix Constants
/// Prefix constants for SI volume and flow rate unit specification
/// \{
#define UNIT   0 //!< use base unit
#define KILO   3 //!< KILO
#define DECI  -1 //!< DECI
#define CENTI -2 //!< CENTI
#define MILLI -3 //!< MILLI
#define MICRO -6 //!< MICRO
/// \} lcp_prefix


//---------------------------------------------------------------------------
/// \addtogroup lcp_timeunit Time Units
/// Time unit identifies for flow rates
/// \{
#define PER_SECOND    1 //!< PER_SECOND
#define PER_MINUTE   60 //!< PER_MINUTE
#define PER_HOUR   3600 //!< PER_HOUR
/// \} lcp_timeunit


/// \} lcp_pumpunits


/// \ingroup lcp_conti
/// \{
/**
 * Device property identifiers that can be used with the LCB_GetDeviceProperty()
 * and LCB_SetDeviceProperty() function to read and write certain device
 * properties of continuous flow pump.
 */
enum LCP_ContiFlowProperties
{
	/**
	 * Use this property ID to set and get the cross flow duration for the
	 * continuous flow.
	 * The cross flow duration is the time the pump running empty decelerates
	 * while the filled pump accelerates.
	 */
	PropertyCrossFlowDuration_s,//!< PropertyCrossFlowDuration_s

	/**
	 * The overlap duration is a time the refilled pump will start earlier than
	 * the empty pump stops.
	 * You can use this time to ensure that the system is already pressurized
	 * when switching over.
	 */
	PropertyOverlapDuration_s,  //!< PropertyOverlapDuration_s

	/**
	 * Returns the minimum flow that is theoretically possible with the
	 * syringe pumps
	 */
	PropertyMinPumpFlow,        //!< PropertyMinPumpFlow

	/**
	 * Returns the maximum refill flow that is possible with the configured
	 * syringe pumps
	 */
	PropertyMaxRefillFlow,      //!< PropertyMaxRefillFlow

	/**
	 * Use this property to set and read the refill flow for the continuous
	 * flow pump.
	 * The refill flow speed limits the maximumFlow() that is possible with
	 * a continuous flow pump.
	 */
	PropertyRefillFlow,         //!< PropertyRefillFlow

	/**
	 * Sets the switching mode for syringe pump switchover if one syringe pump
	 * runs empty
	 */
	PropertySwitchingMode       //!< PropertySwitchingMode
};


/**
 * Supported continuous flow switching modes
 */
enum eSwitchingMode
{
	/**
	 * Cross fade flows of both pumps
	 */
	SwitchingCrossFlow
};
/// \}


//===========================================================================
//                     PUMP API INITIALISATION
//
/// \addtogroup lcp_api_init Pump API Initialisation
/// API specific initialisation functions.
/// This groups defines all functions to setup and initialize the labbCAN
/// pump API properly.
/// \{
//===========================================================================

//---------------------------------------------------------------------------
/// Query number of detected pump devices
/// \retval >= 0 Number of detected pump devices
/// \retval < 0  Error code
///
LCP_Func long LCP_CALL LCP_GetNoOfPumps();


//---------------------------------------------------------------------------
/// Lookup for a pump device by its name.
/// \param[in] pPumpName The name of the device to lookup for
/// \param[out] PumpHandle Handle to pump device or 0 if no pump with given
///             name exists
/// \retval -ERR_NODEV No device with the given name found
/// \retval ERR_NOERR indicates success
///
LCP_Func long LCP_CALL LCP_LookupPumpByName(const char *pPumpName,
	dev_hdl* PumpHandle);


//---------------------------------------------------------------------------
/// Get pump handle by its index.
/// \param[in] Index Index into list of available pump devices
/// \param[out] PumpHandle Handle to pump device or 0 if the given index is
///             out of range
/// \retval -ERR_PARAM_RANGE If the given device index is out of range
/// \retval ERR_NOERR indicates success
///
LCP_Func long LCP_CALL LCP_GetPumpHandle(unsigned char Index,
	dev_hdl* PumpHandle);
/// \} lcp_api_init



//===========================================================================
//                     PUMP CONFIGURATION
//
/// \addtogroup lcp_cfg Pump Configuration
/// Functions for configuration of pump parameters and pump SI units.
/// \{
//===========================================================================

//---------------------------------------------------------------------------
/// This function sets the default volume unit.
/// All parameters of subsequent dosing function calls are given in this new
/// unit. Example to select milliliters as volume unit. Example:
/// \code
/// long Result = LCP_SetVolumeUnit(hPump1, MILLI, LITRES);
/// \endcode
/// \param[in] hPump A valid syringe pump handle
/// \param[in] Prefix The prefix of the SIunit (i.e MILLI - see @ref lcp_prefix)
/// \param[in] VolumeUnit The volume unit identifier (i.e. LITRES - see @ref
///            lcp_volunit)
/// \return Error code - ERR_NOERR indicates success
/// \see LCP_GetVolumeUnit()
///
LCP_Func long LCP_CALL LCP_SetVolumeUnit(dev_hdl hPump,
                                          int    Prefix,
                                          int     VolumeUnit);


//---------------------------------------------------------------------------
/// Queries the current volume unit used for all dosage functions.
/// \param[in] hPump A valid syringe pump handle
/// \param[out] pPrefix Returns the prefix of the SIunit
///             (i.e MILLI - see @ref lcp_prefix)
/// \param[out] pVolumeUnit Returns the volume unit identifier
///            (i.e. LITRES - see @ref lcp_volunit)
/// \return Error code - ERR_NOERR indicates success
/// \see LCP_SetVolumeUnit()
///
LCP_Func long LCP_CALL LCP_GetVolumeUnit(dev_hdl hPump,
	                                      int*   pPrefix,
                                          int*    pVolumeUnit);


//---------------------------------------------------------------------------
/// Sets the flow unit for a certain pump.
/// The flow unit defines the unit to be used for all flow values passed
/// to API functions or retrieved from API functions.
/// \code
/// long Result = LCA_SetFlowUnit(hAxis, MILLI, LITRES, PER_SECOND);
/// \endcode
/// \param[in] hPump A valid syringe pump handle
/// \param[in] Prefix The prefix of the velocity unit (see @ref lcp_prefix)
/// \param[in] VolumeUnit The volume unit (numerator) of the velocity
///            unit (i.e. LITRES - see @ref lcp_volunit)
/// \param[in] TimeUnit The time unit (denominator) of the velocity unit.
///            (i.e. PER_SECOND - see @ref lcp_timeunit)
/// \return Error code - ERR_NOERR indicates success
/// \see LCP_GetFlowUnit()
///
LCP_Func long LCP_CALL LCP_SetFlowUnit(dev_hdl hPump,
                                        int    Prefix,
                                        int     VolumeUnit,
                                        int     TimeUnit);


//---------------------------------------------------------------------------
/// Queries the current flow unit used for passing flow values.
/// \param[in] hPump A valid syringe pump handle
/// \param[out] pPrefix Returns the prefix of the flow unit (see @ref lcp_prefix)
/// \param[out] pVolumeUnit Returns the volume unit (numerator) of the
///             velocity unit (i.e. LITRES - see @ref lcp_volunit)
/// \param[out] pTimeUnit Returns the time unit (denominator) of the flow
///             unit. (i.e. PER_SECOND - see @ref lcp_timeunit)
/// \return Error code - ERR_NOERR indicates success
/// \see LCP_SetFlowUnit()
///
LCP_Func long LCP_CALL LCP_GetFlowUnit(dev_hdl hPump,
                                        int*   pPrefix,
                                        int*    pVolumeUnit,
                                        int*    pTimeUnit);


//---------------------------------------------------------------------------
/// Get maximum flow rate that is realizable with current dosing unit configuration.
/// The maximum flow rate depends on the mechanical configuration of the
/// dosing unit (gear) and on the syringe configuration. If larger syringes
/// are used then larger flow rates are realizable.
/// \param[in] hPump A valid syringe pump handle
/// \param[out] FlowRateMax Returns the maximum flow rate in configured SI unit
/// \return Error code - ERR_NOERR indicates success
///
LCP_Func long LCP_CALL LCP_GetFlowRateMax(dev_hdl hPump, double* FlowRateMax);


//===========================================================================
//                     SYRINGE PUMP CONFIGURATION
//
/// Syringe pump specific functions for configuration.
/// This group defines functions for configuration of syringe pump parameters
/// like configuration of syringe parameters.
//===========================================================================


//---------------------------------------------------------------------------
/// Read syringe parameters.
/// \param[in] hPump A valid syringe pump handle
/// \param[out] pInnerDiameter_mm Inner diameter of the syringe tube in
///             Millimeters.
/// \param[out] pMaxPistonStroke_mm The maximum piston stroke defines the
///                                 maximum position the piston can be moved
///                                 to before it slips out of the syringe tube.
///                                 The maximum piston stroke limits the maximum
///                                 travel range of the syringe pump pusher.
/// \return Error code - ERR_NOERR indicates success
///
LCP_Func long LCP_CALL LCP_GetSyringeParam(dev_hdl hPump,
                                            double *pInnerDiameter_mm,
                                            double *pMaxPistonStroke_mm);


//---------------------------------------------------------------------------
/// Set syringe parameters.
/// If you change the syringe in one device, you need to setup the new
/// syringe parameters to get proper conversion of flow rate und volume
/// units.
/// \param[in] hPump A valid syringe pump handle
/// \param[in]  InnerDiameter_mm  Inner diameter of the syringe tube in
///                               millimetres.
/// \param[in]  MaxPistonStroke_mm  The maximum piston stroke defines the
///                                 maximum position the piston can be moved
///                                 to before it slips out of the syringe tube.
///                                 The maximum piston stroke limits the maximum
///                                 travel range of the syringe pump pusher.
/// \return Error code - ERR_NOERR indicates success
///
LCP_Func long LCP_CALL LCP_SetSyringeParam(dev_hdl hPump,
                                            double  InnerDiameter_mm,
                                            double  MaxPistonStroke_mm);


//---------------------------------------------------------------------------
/// Returns the maximum volume a pump can aspirate into its container
/// (syringe)
/// For some devices like peristaltic pumps the maximum volume is not limited
/// while for other pumps, like syringe pumps, the maximum volume is limited
/// by the maximum travel range of the drive unit and by the maximum piston
/// stroke of the mounted syringe. This function returns the maximum volume
/// the pump can take up with the current container (eg.syringe) configuration
/// \param[in] hPump A valid syringe pump handle
/// \param[out] VolumeMax Returns the maximum volume in configured SI units
/// \return Error code - ERR_NOERR indicates success
///
LCP_Func long LCP_CALL LCP_GetVolumeMax(dev_hdl hPump, double* VolumeMax);
/// \} lcp_cfg

//===========================================================================
//                             PUMP CONTROL
//
/// \addtogroup lcp_control Pump Control
/// Functions to control the pump parameters like flow and volume.
/// This groups defines all functions to control the pump and to control
/// simple dosing tasks like dosing volumes and generating constant flow.
/// \{
//===========================================================================


//---------------------------------------------------------------------------
/// Executes a reference move for a syringe pump.
/// You can use the function LCP_IsPositionSensingInitialized() to find out,
/// if a reference move is required for a certain pump device. A reference
/// move is only required, if the pump does not have an absolute encoder
/// (like the new Nemesys 4 devices Nemesys M and Nemesys S) and if it has
/// been powered off. That means, if you close your application that uses
/// this library and restart it without powering off the pump, then a calibration
/// is not required because the pump keeps its position value as long as it is
/// powered on.
/// \warning A reference move will move the pusher slightly below the zero
/// position. This may cause a damage to a mounted glass syringe. So if you use
/// this function in your software, you should warn the user about this
/// risk and ask him to unmount the syringe.
/// \param[in] hPump A valid pump handle
/// \retval ERR_NOERR indicates success
/// \retval -ERR_DEVNOSUPP is returned if the device has an absolute encoder and
///         a calibration is not required.
/// \see LCP_IsCalibrationFinished(), LCP_IsPositionSensingInitialized()
///
LCP_Func long LCP_CALL LCP_SyringePumpCalibrate(dev_hdl hPump);


//---------------------------------------------------------------------------
/// Pumps fluid with the given flow rate until the requested fill level is
/// reached. Depending on the requested fill level given in Level parameter this
/// function may cause aspiration or dispension of fluid. This function only
/// works properly for pump devices that support a fill level (eg. syringe
/// pumps). Pumps like peristaltic pumps do not support a fill level and the
/// function returns an error for unsupported pump types.
/// \param[in] hPump A valid pump handle
/// \param[in,out] Level The requested fill level. A level of 0 indicates a
///                completely empty container (eg. empty syringe).
/// \param[in,out] Flow The flow rate to use for pumping
/// \retval ERR_NOERR indicates success
/// \retval -ERR_PARAM_RANGE Level or Flow value is out of range
///
LCP_Func long LCP_CALL LCP_SetFillLevel(dev_hdl hPump,
	                                     double  Level,
	                                     double  Flow);


//---------------------------------------------------------------------------
/// Pump a certain volume with a certain flow rate.
/// \param[in] hPump A valid pump handle
/// \param[in] Volume The volume to pump in physical units
///                   negative volumes indicate aspiration
///                   positive volumes indicate dispensing
/// \param[in] Flow   The flow rate to use to pump the volume
/// \retval ERR_NOERR indicates success
/// \retval -ERR_PARAM_RANGE Level or Flow value is out of range
///
LCP_Func long LCP_CALL LCP_PumpVolume(dev_hdl hPump, double Volume, double Flow);


//--------------------------------------------------------------------------
/// Dispense a certain volume with a certain flow rate.
/// \param[in] hPump A valid pump handle
/// \param[in] Volume The volume to dispense in physical units
/// \param[in] Flow   The flow rate to use to dispense the volume
///                   negative flow rates are invalid
/// \retval ERR_NOERR indicates success
/// \retval -ERR_PARAM_RANGE Level or Flow value is out of range
///
LCP_Func long LCP_CALL LCP_Dispense(dev_hdl hPump, double Volume, double Flow);


//--------------------------------------------------------------------------
/// Aspirate a certain volume with a certain flow rate.
/// \param[in] hPump A valid pump handle
/// \param[in] Volume The volume to aspirate in physical units
/// \param[in] Flow   The flow rate to use to aspirate the volume
///                   negative flow rates are invalid
/// \retval ERR_NOERR indicates success
/// \retval -ERR_PARAM_RANGE Level or Flow value is out of ranges
///
LCP_Func long LCP_CALL LCP_Aspirate(dev_hdl hPump, double Volume, double Flow);


//--------------------------------------------------------------------------
/// Generate a continuous flow.
/// \param[in] hPump A valid pump handle
/// \param[in] FlowRate A positive flow rate indicates dispensing
///                     and a negative flow rate indicates aspiration
/// \retval ERR_NOERR indicates success
/// \retval -ERR_PARAM_RANGE Flow value is out of range
///
LCP_Func long LCP_CALL LCP_GenerateFlow(dev_hdl hPump, double FlowRate);


//--------------------------------------------------------------------------
/// Immediately stop pumping.
/// \param[in] hPump A valid pump handle
/// \return Error code - ERR_NOERR indicates success
///
LCP_Func long LCP_CALL LCP_StopPumping(dev_hdl hPump);


//--------------------------------------------------------------------------
/// Immediately stop pumping off all pumps.
/// \return Error code - ERR_NOERR indicates success
///
LCP_Func long LCP_CALL LCP_StopAllPumps();
/// \} lcp_control


//===========================================================================
//                             PUMP STATUS
//
/// \addtogroup lcp_status Pump Status
/// Functions to query the actual pump status, flow and volume.
/// This groups defines all functions to read the actual pump status
/// (pumping or stopped), the actual flow and volume from the device.
/// \{
//===========================================================================



/**
 * Returns true, if the position sensing system is properly initialized.
 * Each pump drive tracks the actual position value (volume value) by an
 * internal position counter / encoder. Some pumps, such as the new Nemesys S
 * and Nemesys M pumps, have an absolute encoder. That means, this encoder
 * always keeps its position, even if the pumps are turned of. For these
 * pumps this function always returns true. Other pumps, like the Nemesys
 * Low Pressure Pump, have an incremental encoder. This encoder loses its
 * position if the pump power is turned off. That means, if such a pump gets
 * powered on, the this function returns false, because the position of the
 * incremental encoder is not initialized yet. To initialize the position
 * of the encoder, you need to do a reference move via LCP_SyringePumpCalibrate()
 * or you need to restore a previously saved encoder position via
 * LCP_RestoreDrivePosCnt().
 * @param[in] hPump A valid pump handle
 * @retval 1 Position sensing is initialized and you can start dosing
 * @retval 0 Position sensor needs to get initialized via LCP_SyringePumpCalibrate()
 *         or by restoring a saved position via LCP_RestoreDrivePosCnt().
 * @retval <0 Error - negative error code
 * \see LCP_SyringePumpCalibrate(), LCP_RestoreDrivePosCnt()
 */
LCP_Func long LCP_CALL LCP_IsPositionSensingInitialized(dev_hdl hPump);


//--------------------------------------------------------------------------
/// Read the actual flow rate.
/// \param[in] hPump A valid pump handle
/// \param[out] pFlowRateIs The actual flow rate demand value
/// \return Error code - ERR_NOERR indicates success
///
LCP_Func long LCP_CALL LCP_GetFlowIs(dev_hdl hPump, double *pFlowRateIs);


//--------------------------------------------------------------------------
/// Read the target volume.
/// This function simply returns the set target volume value
/// \param[in] hPump A valid pump handle
/// \param[out] pTargetVolume Returns the target volume to dose
/// \return Error code - ERR_NOERR indicates success
///
LCP_Func long LCP_CALL LCP_GetTargetVolume(dev_hdl hPump, double *pTargetVolume);


//--------------------------------------------------------------------------
/// Get the already dosed volume.
/// \param[in] hPump A valid pump handle
/// \param[out] pDosedVolume Returns the already dosed volume
/// \return Error code - ERR_NOERR indicates success
///
LCP_Func long LCP_CALL LCP_GetDosedVolume(dev_hdl hPump, double *pDosedVolume);

//--------------------------------------------------------------------------
/// Returns the actual fill level of the pump.
/// This function returns valid results only for pumps that support a fill level
/// (eg. syringe pumps). Peristaltic pumps do not support fill level.
/// For a syringe pump this function returns the current syringe fill level
/// \param[in] hPump A valid pump handle
/// \param[out] pFillLevel Returns the current fill level of the pump container
///                        (eg. syringe)
/// \return Error code - ERR_NOERR indicates success
///
LCP_Func long LCP_CALL LCP_GetFillLevel(dev_hdl hPump, double* pFillLevel);


//--------------------------------------------------------------------------
/// Check if device is currently stopped or dosing.
/// \param[in] hPump A valid pump handle
/// \retval 1 - Device is pumping
/// \retval 0 - Device is stopped
/// \retval <0 - Error code
///
LCP_Func long LCP_CALL LCP_IsPumping(dev_hdl hPump);


//---------------------------------------------------------------------------
/// Checks if calibration is finished.
/// The pump handle given in hPump param needs to be a syringe pump handle
/// \param[in] hPump A valid pump handle
/// \retval 0 - Device is calibrating
/// \retval 1 - Device calibration has finished
/// \retval <0 - Error code
/// \see LCP_SyringePumpCalibrate()
///
LCP_Func long  LCP_CALL LCP_IsCalibrationFinished(dev_hdl hPump);
/// \} lcp_status


//===========================================================================
//                            PUMP DRIVE
//
/// \addtogroup lcp_drv Pump Drive Control
/// Functions to control and maintain the drive that drives the pump.
/// \{
//===========================================================================

//--------------------------------------------------------------------------
/// Query if pump drive is enabled.
/// Only if the pump drive is enabled it is possible to pump fluid
/// \param[in] hPump A valid pump handle
/// \retval 1 - Pump drive is enabled, pumping is possible
/// \retval 0 - Pump drive is disabled - pump head is free running
/// \retval <0 - Error code
///
LCP_Func long LCP_CALL LCP_IsEnabled(dev_hdl hPump);


//--------------------------------------------------------------------------
/// Check if pump is in a fault state.
/// If the device is in fault state then it is necessary to call
/// LCP_ClearFault() to clear the fault state and then LCP_Enable()
/// to enable the pump drive
/// \param[in] hPump A valid pump handle
/// \retval 1 - Pump is in fault state
/// \retval 0 - Pump is not in fault state
/// \retval <0 - Error code - Error reading the fault state
///
LCP_Func long LCP_CALL LCP_IsInFaultState(dev_hdl hPump);


//---------------------------------------------------------------------------
/// Clear fault condition.
/// This is some kind of error acknowledge that clears the last fault and
/// sets the device in an error free state. If the function
/// LCP_IsInFaultState(void) indicates that device is in fault state, then
/// this function may clear the fault. If the device is still in fault state
/// after this function was called then a serious failure occurred
/// \param[in] hPump A valid pump handle
/// \return Error code
///
LCP_Func long LCP_CALL LCP_ClearFault(dev_hdl hPump);


//--------------------------------------------------------------------------
/// Set axis into enabled state.
/// If the function LCP_IsEnabled(void) indicates that the device is
/// disabled then call this function.
/// \param[in] hPump A valid pump handle
/// \return Error code
///
LCP_Func long LCP_CALL LCP_Enable(dev_hdl hPump);


//--------------------------------------------------------------------------
/// Set pump into disabled state.
/// Call this function to remove power from pump drive
/// \param[in] hPump A valid pump handle
/// \return Error code
///
LCP_Func long LCP_CALL LCP_Disable(dev_hdl hPump);


//--------------------------------------------------------------------------
/// Returns the drive handle of pump drive for the given pump.
/// You can pass the drive handle to the motion control library to access
/// the drive functionality (like reading and restoring the position counter)
/// directly.
/// \param[in] hPump A valid pump handle
/// \retval 0 - No pump drive access possible
/// \retval 1 - Pump drive handle
/// \retval <0 - Error code - Error getting pump drive handle
///
LCP_Func dev_hdl LCP_CALL LCP_GetPumpDriveHandle(dev_hdl hPump);


//---------------------------------------------------------------------------
/// Query the value of the internal drive position counter.
/// \see LCP_RestoreDrivePosCnt()
/// \param[in] hPump Valid pump handle
/// \param[out] pPosCntValue Returns the actual value of the position
///                          counter
/// \return Error code - ERR_NOERR indicates success
///
LCP_Func long LCP_CALL LCP_GetDrivePosCnt(dev_hdl hPump, long *pPosCntValue);


//---------------------------------------------------------------------------
/// Restore internal hardware position counter value of pump drive.
/// The function restores the internal position counter value
/// saved with LCA_GetDrivePosCnt().
/// This function is not required and not supported for devices that have
/// an absolute encoder such as the new Nemesys 4 devices Nemesys S and
/// Nemesys M.
/// \note In many drives the actual position value is counted by a
/// quadrature decoder. This internal position counter value will get
/// lost, as soon as the device is switched off. In order to restore
/// this position counter value after power on, an application can
/// query the internal position counter value (LCA_GetDrivePosCnt()), store
/// it persistently into a configuration file and restore it later by calling
/// this function.
/// \see LCP_GetDrivePosCnt()
/// \param[in] hPump Valid pump handle
/// \param[in] PosCntValue The position counter value to restore
/// \retval ERR_NOERR indicates success
/// \retval -ERR_DEVNOSUPP if the device has an absolute encoder and restoring
///         position counter values is not required and not supported.
///
LCP_Func long LCP_CALL LCP_RestoreDrivePosCnt(dev_hdl hPump, long PosCntValue);
/// \} lcp_drv


//===========================================================================
//                            PUMP VALVE
//
/// \addtogroup lcp_valve Pump Valve Control
/// Functions to access the optional valve that may be assigned to a certain
/// pump device.
/// \{
//===========================================================================

//--------------------------------------------------------------------------
/// Returns 1 if this pump has an valve assigned.
/// \param[in] hPump A valid pump handle
/// \retval 0 - No valve assigned to this pump
/// \retval 1 - Valve assigned to this pump
/// \retval <0 - Error code
///
LCP_Func long LCP_CALL LCP_HasValve(dev_hdl hPump);


//--------------------------------------------------------------------------
/// Returns the valve handle of a pump valve for the pump given in hPump
/// parameter.
/// \param[in] hPump A valid pump handle
/// \param[out] ValveHandle Handle to valve device or 0 if no valve with given
///             name exists
/// \retval -ERR_NODEV No device with the given name found
/// \retval ERR_NOERR indicates success
///
LCP_Func long LCP_CALL LCP_GetValveHandle(dev_hdl hPump,
	dev_hdl* ValveHandle);
/// \} lcp_valve


//===========================================================================
//                        AUXILIARY FUNCTIONS
//
/// \addtogroup lcp_common Auxiliary Functions
/// Common pump specific auxiliary functions.
/// \{
//===========================================================================

//---------------------------------------------------------------------------
/// Query name of specific pump.
/// Normally all pumps are named. That means each pump carries a
/// unique name.
/// \param[in]  hPump           Valid pump handle
/// \param[out] pNameStringBuf  Message buffer for storage of error message string
/// \param[in]  StringBufSize   Size of buffer pNameStringBuf in bytes
/// \return Error code - - ERR_NOERR indicates success
///
LCP_Func long LCP_CALL LCP_GetPumpName(dev_hdl  hPump,
                                        char    *pNameStringBuf,
                                        int      StringBufSize);

/// \} lcp_common

//===========================================================================
//                         TIME-TRIGGERED DOSAGE
//
/// \addtogroup lcp_tt Time-triggered dosage
/// Functions to configure and control time-triggered dosage.
/// Time trigger dosage is a feature that enables time-triggered start
/// of dosage processes. Each pump contains batch list. This list stores
/// single batch entries. A batch entry contains the complete configuration
/// for one single time-triggered dosage task. A batch entry contains\n
/// - Flow
/// - Volume
/// - Date and Time
/// - Cycles
/// - Period
/// The flow and volume values are the configuration for the dosage process
/// that is triggered at a certain time. The date and time value configures
/// The absolute date and time, when this dosage will be triggered the first
/// time. The number of cycles configures how often this dosage should be
/// repeated. A value of 0 indicates an infinite repetition. The period
/// configures the time between two consecutive dosages.
/// \{
//===========================================================================

//---------------------------------------------------------------------------
/// Query current number of entries in a pumps batch list.
/// \param[in]  hPump      Valid pump handle
/// \retval >= 0 Number of entries in batch list
/// \retval <0 Error code
///
LCP_Func long LCP_CALL LCP_GetBatchListSize(dev_hdl hPump);


//---------------------------------------------------------------------------
/// Deletes all entries from a pumps batch list
/// \param[in]  hPump      Valid pump handle
/// \return Error code - ERR_NOERR indicates success
///
LCP_Func long LCP_CALL LCP_ClearBatchList(dev_hdl hPump);


//---------------------------------------------------------------------------
/// This function returns a handle to a certain batch entry.
/// To access the parameters of a batch entry, a valid batch entry handle
/// is required. This handle can be obtained by this function
/// \param[in] hPump  Valid pump handle
/// \param[in] Index  Index into internal array of batch entries
/// \param[out] pBatchEntryHdl Handle to the batch entry indexed by Index
///                            param
/// \return Error code - ERR_NOERR indicates success
/// \retval -ERR_PARAM_RANGE - Index parameter is out of range (>= size
///                            of batch list)
/// \note An index does not always identify the same batch entry. The batch
///       entries a stored in a certain order and this order may change
///       during execution or after insertion/deletion of entries
///
LCP_Func long LCP_CALL LCP_GetBatchEntryAtIndex(dev_hdl        hPump,
                                                 unsigned long  Index,
                                                 dev_hdl       *pBatchEntryHdl);


//---------------------------------------------------------------------------
/// This function returns a handle to a certain batch entry.
/// The functions searches for an entry with a certain starting time. The time
/// value identifies the initial starting time.
/// \param[in] hPump  Valid pump handle
/// \param[in] Time Time value (\see LCP_MakeTime())
/// \param[out] pBatchEntryHdl Handle to the batch entry identified by Time
///                            param
/// \return Error code - ERR_NOERR indicates success
///
LCP_Func long LCP_CALL LCP_GetBatchEntry(dev_hdl        hPump,
                                          unsigned long  Time,
                                          dev_hdl       *pBatchEntryHdl);


//---------------------------------------------------------------------------
/// This function returns the configuration of a certain batch entry
/// \param[in] BatchEntryHdl  Valid batch entry handle
/// \param[out] pVolume Returns the volume value
/// \param[out] pFlow Returns the flow value
/// \param[out] pTime Returns the first start time of this batch entry
/// \param[out] pCycles Returns the number of cycles this batch entry should be
///                     executed
/// \param[out] pPeriodSecs Returns the period in seconds
/// \return Error code - ERR_NOERR indicates success
///
LCP_Func long LCP_CALL LCP_GetBatchEntryParam(dev_hdl       BatchEntryHdl,
                                               double        *pVolume,
                                               double        *pFlow,
                                               unsigned long *pTime,
                                               unsigned long *pCycles,
                                               unsigned long *pPeriodSecs);


//---------------------------------------------------------------------------
/// Adds a single entry to list of batch entries
/// \param[in] hPump  Valid pump handle
/// \param[in] Time   The time that triggers first start of this dosage
/// \param[in] Volume The volume to dose
/// \param[in] Flow   The flow rate to use for dosage
/// \param[in] Cycles The number of cycles to repeat this dosage. A value
///                   of 0 indicates an infinite repetition
/// \param[in] PeriodSecs The time in seconds between two consecutive
///                       execution of this dosage batch entry
/// \return Error code - ERR_NOERR indicates success
///
LCP_Func long LCP_CALL LCP_AddBatchEntry(dev_hdl         hPump,
                                          double          Volume,
                                          double          Flow,
                                          unsigned long   Time,
                                          unsigned long   Cycles,
                                          unsigned long   PeriodSecs);


//---------------------------------------------------------------------------
/// Remove batch entry from list of batch entries
/// \param[in] hPump  Valid pump handle
/// \param[in] Time   Indicates the starting time of the batch entry to be
///                   removed
/// \return Error code - ERR_NOERR indicates success
///
LCP_Func long LCP_CALL LCP_RemoveBatchEntry(dev_hdl       hPump,
                                             unsigned long Time);


//---------------------------------------------------------------------------
/// Start processing of batch list
/// \param[in] hPump  Valid pump handle of pump to start
/// \return Error code - ERR_NOERR indicates success
///
LCP_Func long LCP_CALL LCP_StartBatchProcessing(dev_hdl hPump);


//---------------------------------------------------------------------------
/// Stop processing of batch list
/// \param[in] hPump  Valid pump handle of pump to stop
/// \return Error code - ERR_NOERR indicates success
///
LCP_Func long LCP_CALL LCP_StopBatchProcessing(dev_hdl hPump);


//---------------------------------------------------------------------------
/// Check if batch processing is active
/// \param[in] hPump  Valid pump handle of pump to check
/// \retval 0  Batch processing is inactive
/// \retval >0 Batch processing is active
/// \retval <0 Error code - ERR_NOERR indicates success
///
LCP_Func long LCP_CALL LCP_IsBatchRunning(dev_hdl hPump);


//---------------------------------------------------------------------------
/// Returns time of next dosage event
/// \note The function only returns a valid value if the batch is running
///       (\see LCP_IsBatchRunning()). If the batch is not running, then
///       the time value returned is undefined.
/// \param[in] hPump  Valid pump handle of pump to check
/// \retval >=0 Time value of next dosage event
/// \retval <0 Error code
///
LCP_Func long LCP_CALL LCP_GetNextDosageTime(dev_hdl hPump);
/// \} lcp_tt

//===========================================================================
//                      CONTINUOUS FLOW FUNCTIONS
//
/// \addtogroup lcp_conti Continuous Flow Functions
/// Functions for creation and control of continuous flow pumps.
/// \{
//===========================================================================
/**
 * Create a continuous flow pump from two syringe pumps.
 * A continuous flow pump is a "virtual" pump device that is created from
 * two syringe pumps.
 * @param[in] hPump1 Device handle of the first syringe pump.
 * @param[in] hPump2 Device handle of the second syringe pump.
 * @param[out] ContiFlowPumpHandle Device handle of the created continuous flow
 *             pump
 * @return Returns -ERR_INVAL if the pump device handles given in hPump1 and
 *         hPump2 are no syringe pump handles.
 * @note For best results it is recommended that the two given syringe pumps
 * hPump1 and hPump2 should be of the same device type (such as 2 x nemesys M)
 */
LCP_Func long LCP_CALL LCP_CreateContiFlowPump(dev_hdl hPump1, dev_hdl hPump2,
	dev_hdl* ContiFlowPumpHandle);


/**
 * Configures the continuous flow valve for one syringe pump channel
 * of a continuous flow pump.
 * A continuous flow pump consists of two syringe pump and each syringe
 * pump channel has its own continuous flow valve.
 * A continuous flow valve is a "virtual" valve that
 *  - may consist of a 3/2 way valve and a switchable close valve or
 *  - two switchable valves forming a 3/4 way valve or
 *  - one single 3/4 way valve
 * @param[in] hContiFlowPump Continuous flow pump handle create with
 *        LCP_CreateContiFlowPump
 * @param[in] PumpChannelIndex Channel index 0 or 1 for the syringe pump channel 0
 *        or 1 of the given hContiFlowPump
 * @param[in] ValveIndex The index 0 or 1 of the physical valves that form a
 *        continuous flow valve.
 * @param[in] Valve The valve handle of the real valve
 * @param[in] AspiratingPos The target position index for the valve when the pump
 *        channel given in PumpChannelIndex aspirates. Use -1 for no valve
 *        switching
 * @param[in] DispensingPos The target position index for the valve when the pump
 *        channel given in PumpChannelIndex dispenses. Use -1 for no valve
 *        switching
 * @param[in] ClosedPos The target position index for the valve when the pump
 *        channel given in PumpChannelIndex needs a closed valve - e.g
 *        for pre pressurizing.
 * @return Error code - ERR_NOERR indicates success
 */
LCP_Func long LCP_CALL LCP_ConfigureContiFlowValve(dev_hdl hContiFlowPump,
	unsigned int PumpChannelIndex, unsigned int ValveIndex, dev_hdl Valve,
	int AspiratingPos, int DispensingPos, int ClosedPos);


/**
 * Initialize the continuous flow pump.
 * Call this function after all parameters have been set, to prepare the
 * conti flow pump for the start of the continuous flow. The initialization
 * procedure ensures, that the syringes are sufficiently filled to start
 * the continuous flow. So calling this function may cause a syringe refill
 * if the syringes are not sufficiently filled. So before calling this function
 * your should ensure, that syringe refilling properly works an can be
 * executed. If you have a certain syringe refill procedure, you can also
 * manually refill the syringes with the normal syringe pump functions. If the
 * syringes are sufficiently filled if you call this function, no refilling
 * will take place.
 * \note You can interrupt a running initialization procedure by calling the
 * LCP_StopPumping() function.
 * \note You can use the functions LCP_IsContiFlowInitializing() and
 * LCP_IsContiFlowInitialized() to check if the pump is initialized or if
 * initializing is active.
 * \see LCP_IsContiFlowInitializing(), LCP_IsContiFlowInitialized()
 * @param[in] hContiFlowPump Continuous flow pump handle create with
 *        LCP_CreateContiFlowPump
 * @return Error code - ERR_NOERR indicates success
 */
LCP_Func long LCP_CALL LCP_InitializeContiFlow(dev_hdl hContiFlowPump);

/**
 * Returns true, if the conti fow pump initialization is just active.
 * You can use this function to poll for the end for the initialization.
 * @param[in] hContiFlowPump Continuous flow pump handle create with
 *        LCP_CreateContiFlowPump
 * @retval 1 Initialization is running
 * @retval 0 Initialization is not running
 * @retval <0 Error code
 */
LCP_Func long LCP_CALL LCP_IsContiFlowInitializing(dev_hdl hContiFlowPump);


/**
 * Returns true, if the conti fow pump is initialized and ready for continuous
 * flow start.
 * Use this function to check if the pump is initialized before you start a
 * continuous flow. If you change and continuous flow parameter, like
 * valve settings, cross flow duration and so on, the pump will leave the
 * initialized state. That means, after each parameter change, an initialization
 * is required. Changing the flow rate or the dosing volume does not require
 * and initialization.
 * @param[in] hContiFlowPump Continuous flow pump handle create with
 *        LCP_CreateContiFlowPump
 * @retval 1 Conti flow pump is initialized and ready for continuous flow
 * @retval 0 Initialization of conti flow pump is required
 * @retval <0 Error code
 */
LCP_Func long LCP_CALL LCP_IsContiFlowInitialized(dev_hdl hContiFlowPump);


/**
 * Returns the device handle for the syringe pump 1 or 2 of this continuous
 * flow pump.
 * @param[in] hContiFlowPump Continuous flow pump handle create with
 *        LCP_CreateContiFlowPump
 * @param[in] Channel 0 or 1
 * @param[in] SyringePumpHandle Returns the device handle of the syringe pump for
 *        the given Channel.
 * @return Error code - ERR_NOERR indicates success
 */
LCP_Func long LCP_CALL LCP_GetContiFlowSyringePump(dev_hdl hContiFlowPump, unsigned int Channel,
	dev_hdl* SyringePumpHandle);

/// \} lcp_conti


//===========================================================================
//                      FORCE MONITORING FUNCTIONS
//
/// \addtogroup lcp_force Force Monitoring Functions
/// This group contains functions for controlling the force monitoring,
/// reading the force sensor and setting a custom force limit for pump
/// devices that support this functionality such as Nemesys S and Nemesys M.
/// \{
//===========================================================================

/**
 * With this function you can check if the pump given in hPump parameter
 * supports force monitoring functionality
 * @param[in] hPump  Valid pump handle
 * @retval <0 error
 * @retval 0 Pump has no force monitoring functionality
 * @retval 1 Pump has force monitoring functionality
 */
LCP_Func long LCP_CALL LCP_HasForceMonitoring(dev_hdl hPump);


/**
 * Return the force unit used for all force monitoring related functions.
 * @param[in] hPump  Valid pump handle
 * @param[out] Prefix Prefix Returns the prefix of the SIunit
 *             (i.e MILLI - see @ref lcp_prefix)
 * @param[out] ForceUnit Returns the force unit identifier
 *            (i.e. NEWTON - see @ref lcp_forceunit)
 * @return Error code - ERR_NOERR indicates success
 */
LCP_Func long LCP_CALL LCP_GetForceUnit(dev_hdl hPump,
                                        int*    Prefix,
                                        int*    ForceUnit);


/**
 * Enable / Disable force monitoring.
 * @param[in] hPump  Valid pump handle
 * @param[in] Enable 0 = Disable force monitoring, 1 = Enable force monitoring
 * @return Error code - ERR_NOERR indicates success
 */
LCP_Func long LCP_CALL LCP_EnableForceMonitoring(dev_hdl hPump, int Enable);


/**
 * Returns true, if force monitoring is enabled
 * @param[in] hPump  Valid pump handle
 * @retval <0 Error - negative error code
 * @retval 0 Force monitoring disabled
 * @retval 1 Force monitoring enabled
 */
LCP_Func long LCP_CALL LCP_IsForceMonitoringEnabled(dev_hdl hPump);


/**
 * Returns the maximum device force.
 * The maximum device force is the maximum force the pump hardware can
 * take in continuous operation.
 * @param[in] hPump  Valid pump handle
 * @param[out] MaxForce  Returns the maximum device force
 * @return Error code - ERR_NOERR indicates success
 */
LCP_Func long LCP_CALL LCP_GetMaxDeviceForce(dev_hdl hPump, double* MaxForce);


/**
 * Sets a custom force limit.
 * Each device has a device specific force limit. This function allows
 * you to reduce the maximum force below this maximum device force, if
 * this is required for your application. If the given ForceLimit is
 * higher than LCP_GetMaxDeviceForce(), then LCP_GetMaxDeviceForce() will be
 * set as force limit.
 * @param[in] hPump  Valid pump handle
 * @param[in] ForceLimit The force limit in the unit returned by LCP_GetForceUnit()
 * @return Error code - ERR_NOERR indicates success
 */
LCP_Func long LCP_CALL LCP_WriteForceLimit(dev_hdl hPump, double ForceLimit);


/**
 * Returns the force limit.
 * If no custom force limit is set, then this function returns the
 * LCP_GetMaxDeviceForce().
 * @param[in] hPump  Valid pump handle
 * @param[out] ForceLimit Returns the force limit in the unit returned by LCP_GetForceUnit()
 * @return Error code - ERR_NOERR indicates success
 */
LCP_Func long LCP_CALL LCP_GetForceLimit(dev_hdl hPump, double* ForceLimit);


/**
 * Reads the force sensor and returns the measured force in the unit returned
 * by LCP_GetForceUnit().
 * @param[in] hPump  Valid pump handle
 * @param[out] ForceSensorValue Returns the value read from force sensor
 * @return Error code - ERR_NOERR indicates success
 */
LCP_Func long LCP_CALL LCP_ReadForceSensor(dev_hdl hPump, double* ForceSensorValue);


/**
 * Reads the safety stop input.
 * I case of a force overload, that means, if the measured force is higher
 * than the force limit, the force monitoring sets the safety stop input
 * and stops the pump. If this function returns true, then the pump is in
 * a force overload situation. If safety stop is active, you can read the
 * force sensor via LCP_ReadForceSensor() to get the current force value.
 * @param[in] hPump  Valid pump handle
 * @retval <0 Error - negative error code
 * @retval 1 Force safety stop is active - force overload or force monitoring
 *           disabled
 * @retval 0 Force safety stop is not active - normal dosing is possible
 */
LCP_Func long LCP_CALL LCP_IsForceSafetyStopActive(dev_hdl hPump);


/**
 * Clear / acknowledge force safety stop.
 * The force monitoring functionality has a hysteresis.
 * In case of a force overload situation you need to lower the force ca.
 * 0.1 kN to clear the safety stop. If this is not possible, you can lower
 * the force less (for example 0.02 kN) and then call this function to
 * clear the safety stop input. That means, you only need to call this
 * function, if it is not possible for you, to lower the force ca. 0.1 kN
 * below the configured force limit or if you already lowered the force and
 * the safety stop input is still active.
 * @param[in] hPump  Valid pump handle
 * @return Error code - ERR_NOERR indicates success
 */
LCP_Func long LCP_CALL LCP_ClearForceSafetyStop(dev_hdl hPump);

/// \} lcp_force
/// \} lcp_api
//---------------------------------------------------------------------------
#endif // labbCAN_Pump_APIH

