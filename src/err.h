#ifndef __SQ_ERROR__
#define __SQ_ERROR__

// negative error codes originate in the CAEN library, positive error codes are issued by this program

typedef enum SDQ_ERROR{
  SUCCESS = 0L,
  CONFIG_OPEN_ERROR = 1L,
  CONFIG_PARSE_ERROR = 2L
} SDQ_ERROR;


// prints out the error message associated with that int
const char* SDQ_Error_Message(int code);

#endif
