#include <config.h>
#include <ini.h>
#include <string.h>
#include <stdlib.h>

SDQ_ERROR SDQ_ParseConfig(const char* filename, SDQ_Config_t* config){
  if (ini_parse(filename, handler, config) < 0) {
    printf("Can't load '%s'\n", filename);
    return CONFIG_OPEN_ERROR;
  }
  return SUCCESS;
}

int match(const char* s, const char* n, const char* section, const char* name){
  return strcmp(section, s) == 0 && strcmp(name, n) == 0;
}

static int handler(void* user, const char* section, const char* name,
		   const char* value){

  SDQ_Config_t* pconfig = (SDQ_Config_t*)user;

  if (match("settings", "maxEventsRead", section, name)) {
    pconfig->maxEventsRead = atoi(value);
  }
  else if(match("settings", "recordLength", section, name)){
    pconfig->recordLength = atoi(value);
  }
  else if(match("settings", "postTriggerSize", section, name)){
    pconfig->postTriggerSize = atoi(value);
  }
  else if(match("settings", "channel", section, name)){
    pconfig->channel = atoi(value);
  }
  else if(match("settings", "triggerPolarity", section, name)){
    pconfig->triggerPolarity = atoi(value);
  }
  else if(match("settings", "dcOffset", section, name)){
    pconfig->dcOffset = atoi(value);
  }
  else if(match("settings", "triggerThreshold", section, name)){
    pconfig->triggerThreshold = atoi(value);
  }
  else if(match("settings", "polFreq", section, name)){
    pconfig->polFreq = atof(value);
  }
  else if(match("settings", "nReadouts", section, name)){
    pconfig->nReadouts = atoi(value);
  }
  else if(match("settings", "headerFile", section, name)){
    pconfig->headerFile = strdup(value);
  }
  else if(match("settings", "eventDir", section, name)){
    pconfig->eventDir = strdup(value);
  }
  else {
    return 0;  /* unknown section/name, error */
  }
  return 1;
}
		  
SDQ_ERROR SDQ_PrintConfig(SDQ_Config_t config){
  printf("--------------------------------------------------------------------------------\n");
  printf("maxEventsRead = %d\n", config.maxEventsRead);
  printf("recordLength = %d\n", config.recordLength);
  printf("postTriggerSize = %d\n", config.postTriggerSize);
  printf("channel = %d\n", config.channel);
  printf("triggerPolarity = %d\n", config.triggerPolarity);
  printf("dcOffset = %d\n", config.dcOffset);
  printf("triggerThreshold = %d\n", config.triggerThreshold);
  printf("polFreq = %f\n", config.polFreq);
  printf("nReadouts = %d\n", config.nReadouts);
  printf("headerFile = %s\n", config.headerFile);
  printf("eventDir = %s\n", config.eventDir);
  printf("--------------------------------------------------------------------------------\n");

  return SUCCESS;
}


void  SDQ_ConfigToDummy(SDQ_Config_t* config){
  // set these values to something invalid so we can check that the user remembered to specify them in the config file
  config -> maxEventsRead = -1;
  config -> recordLength  = -1;
  config -> postTriggerSize = -1;
  config -> channel = -1;
  config -> triggerPolarity -1;
  config -> dcOffset = -1;
  config -> triggerThreshold = -1;
  config -> polFreq = -1;
  config -> nReadouts = -1;
  strcpy(config -> headerFile, "____");
  strcpy(config -> eventDir, "____");
}


SDQ_ERROR SDQ_CheckConfigAgainstDummy(SDQ_Config_t* config){
  int passes = 1;
  
  if(config -> maxEventsRead == -1){
    passes = 0;
    printf("maxEventsRead missing from config?");
  }

  if(config -> recordLength  == -1){
    passes = 0;
    printf("maxEventsRead missing from config?");
  }
  
  if(config -> postTriggerSize == -1){
    passes = 0;

  }
  
  if(config -> channel == -1){
    passes = 0;
  }

  if(config -> triggerPolarity == -1){
    passes = 0;
  }

  if(config -> dcOffset == -1){
    passes = 0;
  }

  if(config -> triggerThreshold == -1){
    passes = 0;
  }

  if(config -> polFreq == -1){
    passes = 0;
  }

  if(config -> nReadouts == -1){
    passes = 0;
  }

  if(strcmp(config -> eventDir, "") != 0){
    passes = 0;
  }

  if(strcmp(config -> eventDir, "") != 0){
    passes = 0;
  }

  if(!passes)
    return CONFIG_PARSE_ERROR;
  
  return SUCCESS;
}
