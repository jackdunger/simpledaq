#ifndef __SDQ_ACQUISITION__
#define __SDQ_ACQUISITION__
#include <err.h>
#include <config.h>
#include <CAENDigitizer.h>
#include <stdio.h>

SDQ_ERROR SaveEvent(const char* outFile, uint16_t * data, int nSamples);
SDQ_ERROR SDQ_RunAcquisition(SDQ_Config_t config);
SDQ_ERROR ReadoutEvents(int handle, uint32_t channel, char * buffer, FILE* headerFile, const char* eventDir, uint32_t* nEvents);
void CleanUp(int handle, char * buffer);


#endif
