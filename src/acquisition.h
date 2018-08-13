#ifndef __SDQ_ACQUISITION__
#define __SDQ_ACQUISITION__
#include <err.h>
#include <config.h>
#include <CAENDigitizer.h>
#include <stdio.h>


/* The main method, run the aquisition according to the parameters defined in
   config. This is the interface to these functions, the following are used by it.
*/
SDQ_ERROR SDQ_RunAcquisition(SDQ_Config_t config);



/* Creates a directory for storing the output events, if it does not exist already
 */
int OpenEventDir(const char* dirName){


/* Save an event to a text file at path outFile
   data -> the time ordered samples @ 16bit precision
   nSamples -> the number of 4ns samples
   the file must be opened before calling this function, and closed afterwards
*/
SDQ_ERROR SaveEvent(const char* outFile, uint16_t * data, int nSamples);


/* This function does the actual work in talking to the digitizer 
   handle  -> this is the device handle id, assigned when a connection is opened to the device
   channel -> the DAC channel to read from
   buffer  -> used to write the aquired data into memory, malloced in SDQ_RunAcquisition
*/
SDQ_ERROR ReadoutEvents(int handle, uint32_t channel, char * buffer, FILE* headerFile,
                        const char* eventDir, uint32_t* nEvents);

 
/* Clears the sample buffer if it is not NULL and closes the connection to the digitizer.
   Should be called when acquisition finishes or an error occurs.
   
   channel -> the DAC channel to read from
   buffer  -> used to write the aquired data into memory, malloced in SDQ_RunAcquisition
*/
void CleanUp(int handle, char * buffer);


#endif
