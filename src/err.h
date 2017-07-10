#ifndef __SQ_ERROR__
#define __SQ_ERROR__

// negative error codes originate in the CAEN library

typedef enum SDQ_ERROR{
  SUCCESS = 0L,
  CONFIG_MISSING = 1L,
  CONFFG_PARSE_ERROR = 2L
} SDQ_ERROR;


// prints out the error message associated with that int
const char* error_msg(int code);

#endif
