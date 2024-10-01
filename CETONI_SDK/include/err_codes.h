#ifndef err_codesH
#define err_codesH
//===========================================================================
/// \file    err_codes.h
/// \author  Uwe Kindler (UK)
/// \date    2007/03/27
/// \brief   Common error code definitions for error handling.
//
///  This provides a common set of error codes that all
///  packages can agree on. It doesn't preclude them defining
///  their own error return system, but this is a preferable
///  system to use to help error support be as general as
///  possible.
///
///  We try and conform to the ANSI/POSIX error code format,
///  namely starting with the character 'E'.
//===========================================================================


//===========================================================================
//                                INCLUDES
//===========================================================================
#include <stdint.h>
#ifdef USL_BUILD_LIB
// include for internal use only - not required for any API
#include <usl/common/usl_global.h>
#endif

#ifndef USL_EXPORT
#define USL_EXPORT
#endif


//===========================================================================
//                               MACROS
//===========================================================================
/// Checks, if the given value is an error code - it is if value is < 0
#define IS_USL_ERROR(_errcode_) ((_errcode_) < 0)

//===========================================================================
//                             TYPE DEFINITIONS
//===========================================================================

//---------------------------------------------------------------------------
/// Error code type.
/// A type for error codes which may be useful to explain the purpose of
/// a variable or return code. It shows that it contains an error code
/// of the type defined below
///
typedef int32_t TErrCode;


//===========================================================================
//                            CROSS REFERENCES
//===========================================================================

#ifdef __cplusplus
extern "C" {
#endif
//---------------------------------------------------------------------------
/// This function converts error code into error string
/// \param[in] ErrCode Numeric error code to convert into error message 
///                    string
/// \return Error string
///
USL_EXPORT const char* ErrorToString(TErrCode ErrCode);


/**
 * Translates an errno value from standard C errno variable into Usl error code
 */
USL_EXPORT TErrCode errnoToErrCode(int errnum);

#ifdef __cplusplus
}   /* extern "C" */
#endif


//===========================================================================
//                             ERROR CODES
//
/// \addtogroup err_codes Error Codes
///  These identifiers provide a common set of error codes that all
///  packages can agree on. It doesn't preclude them defining
///  their own error return system, but this is a preferable
///  system to use to help error support be as general as
///  possible.
///
///  We try and conform to the ANSI/POSIX error code format,
///  namely starting with the character 'E'
/// \attention All error codes will be returned as negative values. That
///            means a function does not return ERR_PERM but it returns
///            -ERR_PERM. That means you simply need to check for negative
///            return values to detect errors.
/// \{
//===========================================================================


//---------------------------------------------------------------------------
/// \addtogroup err_common Common error codes
/// \{
#define ERR_NOERR           0x0000     ///< No error
#define ERR_PERM            0x0001     ///< Not permitted
#define ERR_NOENT           0x0002     ///< No such entity
#define ERR_SRCH            0x0003     ///< No such process
#define ERR_INTR            0x0004     ///< Operation interrupted 
#define ERR_IO              0x0005     ///< I/O error 
#define ERR_2BIG            0x0006     ///< Argument list too long
#define ERR_NOEXEC          0x0007     ///< Executable format error
#define ERR_CHILD           0x0008     ///< No child process
#define ERR_BADF            0x0009     ///< Bad file handle
#define ERR_MLINK           0x000A     ///< Too many links
#define ERR_AGAIN           0x000B     ///< Try again later
#define ERR_WOULDBLOCK      ERR_AGAIN ///< \see ERR_AGAIN
#define ERR_NOMEM           0x000C    ///< Out of memory 
#define ERR_ACCES			0x000D	  ///< Permission denied
#define ERR_FAULT			0x000E	  ///< Bad address
#define ERR_NOLCK           0x000F    ///< No lock available
#define ERR_BUSY            0x0010    ///< Resource busy
#define ERR_XDEV            0x0012    ///< Cross-device link
#define ERR_NODEV           0x0013    ///< No such device
#define ERR_NOTDIR          0x0014    ///< Not a directory
#define ERR_ISDIR           0x0015    ///< Is a directory
#define ERR_INVAL           0x0016    ///< Invalid argument
#define ERR_NFILE           0x0017    ///< Too many open files in system
#define ERR_MFILE           0x0018    ///< Too many open files
#define ERR_NOTTY			0x0019	  ///< Not a typewriter
#define ERR_FBIG            0x001B    ///< File too large
#define ERR_NOSPC           0x001C    ///< No space left on device
#define ERR_SPIPE           0x001D    ///< Illegal seek
#define ERR_ROFS            0x001E    ///< Read-only file system
#define ERR_ILSEQ           0x001F    ///< Illegal byte sequence
#define ERR_PIPE2			0x0020	  ///< Broken pipe
#define ERR_DOM             0x0021    ///< Argument to math function outside valid domain
#define ERR_RANGE           0x0022    ///< Math result cannot be represented
#define ERR_DEADLK          0x0023    ///< Resource deadlock would occur 
#define ERR_DEADLOCK        ERR_DEADLK///< \see ERR_DEADLK
#define ERR_CANCELED        0x0024    ///< Operation canceled
#define ERR_OVERFLOW        0x0025    ///< Value too large
#define ERR_NOSYS           0x0026    ///< Function not implemented
#define ERR_OWNERDEAD       0x0027    ///< Owner dead
#define ERR_LOOP			0x0028    ///< Too many symbolic links encountered
#define ERR_NAMETOOLONG     0x003C    ///< File name too long     
#define ERR_NOTEMPTY        0x0042    ///< Directory not empty 
#define ERR_NOTSOCK			0x0058	  ///< Socket operation on non-socket
#define ERR_DESTADDRREQ		0x0059	  ///< Destination address required
#define ERR_NOPROTOOPT		0x005C	  ///< Protocol not available
#define ERR_PROTONOSUPPORT	0X005D	  ///< Protocol not supported
#define ERR_NOTSUP          0x005F    ///< Not supported error 
#define ERR_AFNOSUPPORT		0x0061	  ///< Address family not supported by protocol
#define ERR_ADDRINUSE		0x0062	  ///< Address already in use
#define ERR_ADDRNOTAVAIL	0x0063	  ///< Cannot assign requested address
#define ERR_NOBUFS			0X0069	  ///< No buffer space available
#define ERR_EDQUOT			0x007A	  ///< Quota exceeded
#define ERR_NOTBLK          0x007B    ///< Block device required
#define ERR_TXTBSY          0x007C    ///< Text file busy
#define ERR_NOMSG           0x007D    ///< No message of desired type
#define ERR_IDRM            0x007E    ///< Identifier removed
#define ERR_CHRNG           0x007F    ///< Channel number out of range

#define ERR_L2NSYNC         0x0080    ///<  Level 2 not synchronized
#define ERR_L3HLT           0x0081    ///<  Level 3 halted
#define ERR_L3RST           0x0082    ///<  Level 3 reset
#define ERR_LNRNG           0x0083    ///<  Link number out of range
#define ERR_UNATCH          0x0084    ///<  Protocol driver not attached
#define ERR_NOCSI           0x0085    ///<  No CSI structure available
#define ERR_L2HLT           0x0086    ///<  Level 2 halted
#define ERR_BADE            0x0087    ///<  Invalid exchange
#define ERR_BADR            0x0088    ///<  Invalid request descriptor
#define ERR_XFULL           0x0089    ///<  Exchange full
#define ERR_NOANO           0x008A    ///<  No anode
#define ERR_BADRQC          0x008B    ///<  Invalid request code
#define ERR_BADSLT          0x008C    ///<  Invalid slot

#define ERR_EOF             0x00C8    ///< End of file reached
#define ERR_NOSUPP          0x00C9    ///< Operation not supported 
#define ERR_DEVNOSUPP       0x00CA    ///< Device does not support this operation
#define ERR_UNKNOWN         0x00CB    ///< Unknown error or unknown error code

#define ERR_TIMEOUT         0x00D0    ///< an operation timed out
/// \} err_common


//---------------------------------------------------------------------------
/// \addtogroup err_network Additional errors used by networking
/// \{
#define ERR_NET_NXIO            0x012C   ///< Device not configured
#define ERR_NET_ACCES           0x012D   ///< Permission denied
#define ERR_NET_EXIST           0x012E   ///< File exists
#define ERR_NET_NOTTY           0x012F   ///< Inappropriate ioctl for device
#define ERR_NET_PIPE            0x0130   ///< Broken pipe
/// \} err_network


//---------------------------------------------------------------------------
/// \addtogroup err_nonblock Non-blocking and interrupt i/o
/// \{
#define ERR_INPROGRESS      0x0136   ///< Operation now in progress
#define ERR_ALREADY         0x0137   ///< Operation already in progress
/// \} err_nonblock


//---------------------------------------------------------------------------
/// \addtogroup err_ipc_arg IPC/network software -- argument errors
/// \{
#define ERR_NET_NOTSOCK         0x0140   ///< Socket operation on non-socket
#define ERR_NET_DESTADDRREQ     0x0141   ///< Destination address required
#define ERR_NET_MSGSIZE         0x0142   ///< Message too long
#define ERR_NET_PROTOTYPE       0x0143   ///< Protocol wrong type for socket
#define ERR_NET_NOPROTOOPT      0x0144   ///< Protocol not available
#define ERR_NET_PROTONOSUPPORT  0x0145   ///< Protocol not supported
#define ERR_NET_SOCKTNOSUPPORT  0x0146   ///< Socket type not supported
#define ERR_NET_OPNOTSUPP       0x0147   ///< Operation not supported
#define ERR_NET_PFNOSUPPORT     0x0148   ///< Protocol family not supported
#define ERR_NET_AFNOSUPPORT     0x0149   ///< Address family not supported by
                                      ///< protocol family 
#define ERR_NET_ADDRINUSE       0x014A   ///< Address already in use
#define ERR_NET_ADDRNOTAVAIL    0x014B   ///< Can't assign requested address
/// \} err_ipc_arg


//---------------------------------------------------------------------------
/// \addtogroup err_ipc_op IPC/network software -- operational errors
/// \{
#define ERR_NET_NETDOWN         0x015E  ///< Network is down
#define ERR_NET_NETUNREACH      0x015F   ///< Network is unreachable
#define ERR_NET_NETRESET        0x0160   ///< Network dropped connection on reset
#define ERR_NET_CONNABORTED     0x0161   ///< Software caused connection abort
#define ERR_NET_CONNRESET       0x0162   ///< Connection reset by peer
#define ERR_NET_NOBUFS          0x0163   ///< No buffer space available
#define ERR_NET_ISCONN          0x0164   ///< Socket is already connected
#define ERR_NET_NOTCONN         0x0165   ///< Socket is not connected
#define ERR_NET_SHUTDOWN        0x0166   ///< Can't send after socket shutdown
#define ERR_NET_TOOMANYREFS     0x0167   ///< Too many references: can't splice
#define ERR_NET_TIMEDOUT        0x0168   ///< Operation timed out
#define ERR_NET_CONNREFUSED     0x0169   ///< Connection refused

#define ERR_NET_HOSTDOWN        0x016C   ///< Host is down
#define ERR_NET_HOSTUNREACH     0x016D   ///< No route to host
/// \} err_ipc_op


//---------------------------------------------------------------------------
/// \addtogroup err_add_user Additional user defined error codes
/// \{
#define ERR_ABORT           0x0200   ///< user aborted something
#define ERR_PARAM_RANGE     0x0201   ///< value range of parameter exceeded
#define ERR_ERROR           0x0202   ///< common unspecified error
#define ERR_EXCEPTION       0x0203   ///< application has thrown an exception
#define ERR_DEVCFG          0x0204   ///< invalid device configuration
#define ERR_DEVSTATE        0x0205   ///< wrong device state for this operation
#define ERR_LISTEMPTY       0x0206   ///< could not execute an operation because of an empty list
#define ERR_NO_DATA         0x0207   ///< No data available
#define ERR_DATA_EXIST      0x0208   ///< Object, data or instance already exists
#define ERR_PLUGIN_LOAD     0x0209   ///< Plugin loading error - plugin not found or plugin is not a valid shared library
#define ERR_READ_ONLY       0x020A   ///< Write access to read-only data
/// \} err_add_user


//---------------------------------------------------------------------------
/// \addtogroup err_comm Generic communication protocol specific error codes
/// \{
#define ERR_COMM_DLL              0x0240 ///< data link layer error (error of rs232 connection)
#define ERR_COMM_DLL_TIMEOUT      0x0241 ///< timeout during serial RS232 operation
#define ERR_COMM_HW               0x0242 ///< RS232 interface hardware error
#define ERR_COMM_PROT             0x0243 ///< common RS232 protocol error
#define ERR_COMM_PROT_CRC         0x0244 ///< RS232 CRC error
#define ERR_COMM_PROT_CMD         0x0246 ///< illegal or unknown RS232 command
#define ERR_COMM_PROT_ACKN        0x0247 ///< RS232 interface: receive acknowledge 'F' or no 'O'
#define ERR_COMM_PROT_DATA_LEN    0x0248 ///< RS232 interface: wrong data length code
#define ERR_COMM_PROT_FRAME       0x0249 ///< RS232 interface: invalid frame format
/// \} err_comm


//---------------------------------------------------------------------------
/// \addtogroup err_cano_dll CANopen Data link layer errors
/// \{
#define ERR_CANO_DLL                   0x0300 ///< CAN Data link layer error
#define ERR_CANO_DLL_HWERR             0x0301 ///< hardware error of CAN controller
#define ERR_CANO_DLL_TXFULL            0x0302 ///< TX queue of CAN controller is full
#define ERR_CANO_DLL_WARNING_RX        0x0303 ///< CAN TX error counter (TEC) reached warning level (>96)
#define ERR_CANO_DLL_WARNING_TX        0x0304 ///< CAN RX error counter (REC) reached warning level (>96)
#define ERR_CANO_DLL_ERR_PASSIVE       0x0305 ///< CAN "error passive" occurred
#define ERR_CANO_DLL_BUS_OFF           0x0306 ///< CAN "bus off" error occurred
#define ERR_CANO_DLL_OVERRUN_RX        0x0307 ///< overrun in CAN RX queue or hardware occurred
#define ERR_CANO_DLL_OVERRUN_TX        0x0308 ///< overrun in CAN TX queue occurred
#define ERR_CANO_DLL_CAN_ERR           0x0309 ///< a CAN bit or frame error occurred
#define ERR_CANO_DLL_ARBITRATION_LOST  0x030A ///< CAN arbitration lost - this is not really an error, its more an event
#define ERR_CANO_DLL_PHY_FAULT         0x030B ///< General failure of physical CAN layer detected (if supported by hardware)
#define ERR_CANO_DLL_PHY_H_FAULT       0x030C ///< Fault on CAN-H detected (Low Speed CAN)
#define ERR_CANO_DLL_PHY_L_FAULT       0x030D ///< Fault on CAN-L detected (Low Speed CAN)
#define ERR_CANO_DLL_HWSWERR           0x030E ///< Function could not be performed because of CAN interface hard- or software errors
#define ERR_CANO_DLL_RES               0x030F ///< CAN interface resource error - The resource limit exceeded at creation of a queue or something else
#define ERR_CANO_DLL_TX                0x0310 ///< A CAN message couldn't be sent for a long time - cable error, wrong baud rate etc.
#define ERR_CANO_DLL_HW_NOT_FOUND      0x0311 ///< if CAN hardware could not be found - i.e. when detecting USB devices
#define ERR_CANO_DLL_HW_NOT_AVAILABLE  0x0312 ///< if CAN hardware is detected but could not be used or initialized
#define ERR_CANO_DLL_SUPP              0x0313 ///< CAN interface function is not supported this way
#define ERR_CANO_DLL_PARA              0x0314 ///< CAN interface: Calling parameter(s) is (are) not correct or out of range
#define ERR_CANO_DLL_CFG               0x0315 ///< Configuration of CAN interface device failed or configuration not supported
#define ERR_CANO_DLL_RXQUEUE_EMPTY     0x0316 ///< no message received because RX queue of CAN controller is empty
#define ERR_CANO_DLL_NOT_INITIALIZED   0x0317 ///< can not send message because CAN hardware is not initialized
#define ERR_CANO_DLL_BAUDRATE		   0x0318 ///< Desired baud rate is not supported by this CAN interface
#define ERR_CANO_DLL_TIMEOUT           0x0319 ///< timeout executing CAN interface operation
#define ERR_CANO_DLL_DEVICE_DRIVER     0x031A ///< Error loading CAN controller device driver
#define ERR_CANO_DLL_BUF_OVERFLOW      0x0320 ///< CAN controller buffer overflow error
#define ERR_CANO_DLL_CAN_SOCKETERR	   0x0321 ///< Accessing socket of CAN interface
#define ERR_CANO_DLL_CAN_HW_REMOVED    0x0322 ///< CAN hardware has been removed. Either a USB connector has been unplugged or there is another problem with the CAN hardware.
#define ERR_CANO_TX_NOT_CONNECTED      0x0333 ///< A CAN message couldn't be sent because the CAN interface is not initialized or not connected
/// \}  err_cano_dll


//---------------------------------------------------------------------------
/// \addtogroup err_cano_cal CANopen application layer errors
/// \{
#define ERR_CANO_CAL                   0x0340  ///< CAN application layer error
#define ERR_CANO_CAL_NO_DEVICES        0x0341  ///< no devices detected on bus
/// \}  err_cano_cal


//---------------------------------------------------------------------------
/// \addtogroup err_cano_sdo CANopen SDO transfer errors
/// \{
#define ERR_CANO_SDO                      0x0400 ///< SDO transfer errors
#define ERR_CANO_SDO_ABORT                0x0401 ///< SDO transfer aborted
#define ERR_CANO_SDO_ABORT_TOGGLE_BIT     0x0402 ///< toggle bit not altered
#define ERR_CANO_SDO_ABORT_TIMEOUT        0x0403 ///< SDO protocol timed out
#define ERR_CANO_SDO_ABORT_CMD            0x0404 ///< command specifier not valid or unknown
#define ERR_CANO_SDO_ABORT_BLOCK_SIZE     0x0405 ///< invalid block size in block mode
#define ERR_CANO_SDO_ABORT_SEQ_NUM        0x0406 ///< invalid sequence number in block mode
#define ERR_CANO_SDO_ABORT_CRC            0x0407 ///< CRC error (block mode only)
#define ERR_CANO_SDO_ABORT_OUT_OF_MEM     0x0408 ///< Out of memory
#define ERR_CANO_SDO_ABORT_UNSUPPORTED    0x0409 ///< unsupported access to an object
#define ERR_CANO_SDO_ABORT_WRITEONLY      0x040A ///< attempt to read a write only object
#define ERR_CANO_SDO_ABORT_READONLY       0x040B ///< attempt to write a read only object
#define ERR_CANO_SDO_ABORT_NOT_EXIST      0x040C ///< Object does not exist
#define ERR_CANO_SDO_ABORT_NO_MAP         0x040D ///< object cannot be mapped to the PDO
#define ERR_CANO_SDO_ABORT_MAP_LEN        0x040E ///< number and length of object to be mapped exceeds PDO length
#define ERR_CANO_SDO_ABORT_PRAM_INCOMP    0x040F ///< general parameter incompatibility reasons
#define ERR_CANO_SDO_ABORT_DEV_INCOMP     0x0410 ///< general internal incompatibility in device
#define ERR_CANO_SDO_ABORT_HW             0x0411 ///< access failed due to hardware error
#define ERR_CANO_SDO_ABORT_TYPE_MISMATCH  0x0412 ///< data type does not match, length of service parameter does not match
#define ERR_CANO_SDO_ABORT_DATA_LONG      0x0413 ///< data type does not match, length of service parameter too high
#define ERR_CANO_SDO_ABORT_DATA_SHORT     0x0414 ///< data type does not match, length of service parameter too short
#define ERR_CANO_SDO_ABORT_SUB_UNKNOWN    0x0415 ///< sub index does not exist
#define ERR_CANO_SDO_ABORT_VALUE_INVALID  0x0416 ///< invalid value
#define ERR_CANO_SDO_ABORT_VALUE_HIGH     0x0417 ///< value range of parameter written too high
#define ERR_CANO_SDO_ABORT_VALUE_LOW      0x0418 ///< value range of parameter written too low
#define ERR_CANO_SDO_ABORT_MAX_LESS_MIN   0x0419 ///< maximum value is less than minimum value
#define ERR_CANO_SDO_ABORT_NO_RESOURCE    0x041A ///< Resource not available: SDO connection
#define ERR_CANO_SDO_ABORT_GENERAL        0x041B ///< general error
#define ERR_CANO_SDO_ABORT_DATA_TRANSF    0x041C ///< data cannot be transfered or stored to application
#define ERR_CANO_SDO_ABORT_DATA_LOC_CTRL  0x041D ///< data cannot be transfered or stored to application because of local control
#define ERR_CANO_SDO_ABORT_DATA_DEV_STATE 0x041E ///< data cannot be transfered or stored to application because of present device state
#define ERR_CANO_SDO_ABORT_DATA_OD        0x041F ///< object dictionary not present or dynamic generation fails
#define ERR_CANO_SDO_ABORT_NO_DATA        0x0420 ///< No data available
#define ERR_CANO_SDO_ABORT_MAN_SPECIFIC   0x04FF ///< manufacturer specific error code
/// \}  err_cano_sdo


//---------------------------------------------------------------------------
/// \addtogroup err_cano_lss CANopen LSS transfer errors
/// \{
#define ERR_CANO_LSS_TIMEOUT	          0x0501 ///< LSS communication timed out
#define ERR_CANO_LSS_NODEID_RANGE         0x0502 ///< Configured node id is out of range error
#define ERR_CANO_LSS_SWITCH_SELECTIVE     0x0503 ///< LSS slave could not be set to configuration state
#define ERR_CANO_LSS_MAN_SPECIFIC         0x0504 ///< Manufacturer specific LSS error

/// \}  err_cano_lss


//---------------------------------------------------------------------------
/// \addtogroup err_cano_dev CANopen device profile specific errors
/// \{
#define ERR_CANO_DEVPROF                    0x0600  ///< device profile specific errors
#define ERR_DS401                           0x0620  ///< CANopen DS401 specific error codes
#define ERR_DS402                           0x0640  ///< CANopen DS402 specific error codes
#define ERR_DS402_TIMEOUT_OPMODE_ACTIVATION 0x0641  ///< Error activating a certain drive operation mode
#define ERR_DS402_TIMEOUT_STATUSWORD        0x0642  ///< Timeout waiting for status word
#define ERR_DS402_TIMEOUT_STATUSWORD_PDO    0x0643  ///< Timeout waiting for status word PDO transmission
#define ERR_DS402_DRV_ENABLE_FAULT_STATE    0x0644  ///< Setting drive into operation enabled state is not possible because drive is in fault state. Clear fault state first
#define ERR_DS402_DRV_DISABLE_FAULT_STATE   0x0645  ///< Setting drive into operation enabled state is not possible because drive is in fault state. Clear fault state first
#define ERR_DS402_DRV_ENABLE_TIMEOUT        0x0646  ///< Timeout setting drive to state operation enabled
#define ERR_DS402_DRV_STATE_FAULT_REACTION  0x0647  ///< Timeout while waiting for the completion of the error reaction time
#define ERR_DS402_POSITION_RESET            0x0648  ///< Timeout or error resetting position counter

#define ERR_DS434							0x660	///< CANopen DS434 specific error codes
#define ERR_DS434_TIMEOUT_PUMP_STATUS_WORD	0x661	///< Timeout waiting for pump status word

#define ERR_C_ERRNO                         0x4000  ///< Standard C specific errno error codes ored with 0x4000
#define ERR_APP                             0x8000  ///< application specific errors start here
/// \}  err_cano_dev
/// \} err_codes
//---------------------------------------------------------------------------
#endif // err_codesH

