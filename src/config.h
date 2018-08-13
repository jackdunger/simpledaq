// Simple stuff for parsing a config file into a c struct
#ifndef __SDQ_CONFIG__
#define __SDQ_CONFIG__
#include <CAENDigitizerType.h>
#include <err.h>

// this defines the configuration for a single run
// it is filled from a .ini file using the functions in this unit
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



/* call the ini library, and pass it the handler function defined in this unit,
   fill the config object and return an error code
*/
SDQ_ERROR SDQ_ParseConfig(const char* filename, SDQ_Config_t* config);


/* used by the ini parser to read the correct fields and assign them the correct types.
   Checks section and name against each of the expected fields and uses value to 
   set the correponding value in a config struct. 
   
   user     -> used to point to the config struct to fill
   section  -> section of the .ini file being read
   name     -> name of the field in .ini file being read
   value    -> the correponding value in the .ini file
 */
static int handler(void* user, const char* section, const char* name,
		   const char* value);



/* check the field section + name against a reference so you can determine
   which entry you are looking at when parsing the .ini file.
       s, section -> the section fields to compare
       n, name    -> the name fields to compare
       returns 1 iif s == section and n == name
*/
int match(const char* s, const char* n, const char* section, const char* name
);



/* set every value contained in the struct to a dummy value. Each of these values
   should be overwritten when the config file is read, so these values can be used
   to detect missing parameters.
*/
void  SDQ_ConfigToDummy(SDQ_Config_t* config);



/* check a configuration struct against the dummy values,.
   if one of the fields has a dummy value, it has been omitted
   by the user in the .ini file.
*/
SDQ_ERROR SDQ_CheckConfigAgainstDummy(SDQ_Config_t* config);



/* string format the config struct and print it to screen in this format
   ----------
   <key_name> = <value>
   ---------
   ...
*/
SDQ_ERROR SDQ_PrintConfig(SDQ_Config_t config);
#endif
