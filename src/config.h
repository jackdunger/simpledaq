// Simple stuff for parsing a config file into a c struct
#ifndef __SDQ_CONFIG__
#define __SDQ_CONFIG__
#include <CAENDigitizerType.h>
#include <err.h>

typedef struct{
  uint32_t maxEventsRead;
  uint32_t recordLength;
  uint32_t postTriggerSize;
  uint32_t channel;
  uint32_t triggerPolarity;
  uint32_t dcOffset;
  uint32_t triggerThreshold;
  float    polFreq;
  int      nReadouts;
  char*    headerFile;
  char*    eventDir;
} SDQ_Config_t;

SDQ_ERROR SDQ_ParseConfig(const char* filename, SDQ_Config_t* config);

static int handler(void* user, const char* section, const char* name,
		   const char* value);

int match(const char* s, const char* n, const char* section, const char* name
);

void  SDQ_ConfigToDummy(SDQ_Config_t* config);
SDQ_ERROR SDQ_CheckConfigAgainstDummy(SDQ_Config_t* config);
SDQ_ERROR SDQ_PrintConfig(SDQ_Config_t config);
#endif
