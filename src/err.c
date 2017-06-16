#include <err.h>

// X-macro to print out the error as a nice string
#define ERROR_CODES(X)                                                                                            \
  X(0,    SUCCESS,                           " No error at all! ")	                 	                  \
  X(-1, CAEN_DGTZ_CommError,                 " Communication error ")		                                  \
  X(-2, CAEN_DGTZ_GenericError,              " Unspecified error ")                                               \
  X(-3, CAEN_DGTZ_InvalidParam,              " Invalid parameter ")                                               \
  X(-4, CAEN_DGTZ_InvalidLinkType,           " Invalid Link Type")                                                \
  X(-5, CAEN_DGTZ_InvalidHandle,             " Invalid device handle ")                                           \
  X(-6, CAEN_DGTZ_MaxDevicesError,           " Maximum number of devices exceeded")                               \
  X(-7, CAEN_DGTZ_BadBoardType,              " The operation is not allowed on this type of board")               \
  X(-8, CAEN_DGTZ_BadInterruptLev,           " The interrupt level is not allowed")                               \
  X(-9, CAEN_DGTZ_BadEventNumber,            " The event number is bad")                                          \
  X(-10, CAEN_DGTZ_ReadDeviceRegisterFail,   " Unable to read the registry")                                      \
  X(-11, CAEN_DGTZ_WriteDeviceRegisterFail,  " Unable to write into the registry")                                \
  X(-13, CAEN_DGTZ_InvalidChannelNumber,     " The channel number is invalid")                                    \
  X(-14, CAEN_DGTZ_ChannelBusy,              " The Channel is busy")                                              \
  X(-15, CAEN_DGTZ_FPIOModeInvalid,          " Invalid FPIO Mod")                                                 \
  X(-16, CAEN_DGTZ_WrongAcqMode,             " Wrong acquisition mode")                                           \
  X(-17, CAEN_DGTZ_FunctionNotAllowed,       " This function is not allowed for this module")                     \
  X(-18, CAEN_DGTZ_Timeout,                  " Communication Timeout ")                                           \
  X(-19, CAEN_DGTZ_InvalidBuffer,            " The buffer is invalid ")                                           \
  X(-20, CAEN_DGTZ_EventNotFound,            " The event is not found ")                                          \
  X(-21, CAEN_DGTZ_InvalidEvent,             " The vent is invalid ")                                             \
  X(-22, CAEN_DGTZ_OutOfMemory,              " Out of memory ")                                                   \
  X(-23, CAEN_DGTZ_CalibrationError,         " Unable to calibrate the board ")                                   \
  X(-24, CAEN_DGTZ_DigitizerNotFound,        " Unable to open the digitizer ")                                    \
  X(-25, CAEN_DGTZ_DigitizerAlreadyOpen,     " The Digitizer is already open ")                                   \
  X(-26, CAEN_DGTZ_DigitizerNotReady,        " The Digitizer is not ready to operate ")                           \
  X(-27, CAEN_DGTZ_InterruptNotConfigured,   " The Digitizer has not the IRQ configured ")                        \
  X(-28, CAEN_DGTZ_DigitizerMemoryCorrupted, " The digitizer flash memory is corrupted ")                         \
  X(-29, CAEN_DGTZ_DPPFirmwareNotSupported,  " The digitizer dpp firmware is not supported in this lib version ") \
  X(-30, CAEN_DGTZ_InvalidLicense,           " Invalid Firmware License ")                                        \
  X(-31, CAEN_DGTZ_InvalidDigitizerStatus,   " The digitizer is found in a corrupted status ")                    \
  X(-32, CAEN_DGTZ_UnsupportedTrace,         " The given trace is not supported by the digitizer ")               \
  X(-33, CAEN_DGTZ_InvalidProbe,             " The given probe is not supported for the given digitizer's trace ")\
  X(-99, CAEN_DGTZ_NotYetImplemented,        " The function is not yet implemented ")                             \
  X(1,   CONFIG_OPEN_ERROR,                  " Unable to open specified configuration file ")                     \
  X(2,   CONFIG_PARSE_ERROR,                 " Failed to parse specified configuration file ")                    \
  



#define ERROR_ENUM(ID, NAME, TEXT) NAME = ID,
#define ERROR_TEXT(ID, NAME, TEXT) case ID: return TEXT;


// prints out the error message associated with that int
const char* SDQ_Error_Message(int code){
  switch (code) {
    ERROR_CODES(ERROR_TEXT)
      }

  return "Unknown error";
}
