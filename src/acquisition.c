#include <acquisition.h>
#include <CAENDigitizer.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int OpenEventDir(const char* dirName){
  struct stat st = {0};
  int err = 0;
  if (stat(dirName, &st) == -1) {
    err = mkdir(dirName, 0700);
  }
  return err;
}

void CleanUp(int handle, char * buffer){
  if(buffer)
    CAEN_DGTZ_FreeReadoutBuffer(&buffer);
  CAEN_DGTZ_Reset(handle);
}

SDQ_ERROR SDQ_RunAcquisition(SDQ_Config_t config){
  // first open the connection to the digitizer
  int devHandle;
  CAEN_DGTZ_ErrorCode err = CAEN_DGTZ_OpenDigitizer(CAEN_DGTZ_USB, 0,
						   0, 0, &devHandle);

  if(err){
    printf("can't open connection to device\n");
    CleanUp(devHandle, NULL);
    return err;
  }
  
  // now use the configuration file
  err = CAEN_DGTZ_SetMaxNumEventsBLT(devHandle,
				     config.maxEventsRead
				     );

  err = CAEN_DGTZ_SetRecordLength(devHandle, config.recordLength);
  
  err = CAEN_DGTZ_SetPostTriggerSize(devHandle, config.postTriggerSize);
  err = CAEN_DGTZ_SetChannelEnableMask(devHandle, 1 << config.channel);
  err = CAEN_DGTZ_SetAcquisitionMode(devHandle, CAEN_DGTZ_SW_CONTROLLED);
  err = CAEN_DGTZ_SetChannelSelfTrigger(devHandle,
					CAEN_DGTZ_TRGMODE_ACQ_ONLY,
					1 << config.channel);

  err = CAEN_DGTZ_SetTriggerPolarity(devHandle, config.channel, config.triggerPolarity);
  err = CAEN_DGTZ_SetChannelDCOffset(devHandle, config.channel, config.dcOffset);
  
  err = CAEN_DGTZ_SetChannelTriggerThreshold(devHandle,
					     config.channel,
					     config.triggerThreshold
					     );
  

  // create a buffer to read out into
  uint32_t bufSize = 0;
  char * buffer = NULL;
  err = CAEN_DGTZ_MallocReadoutBuffer(devHandle, &buffer, &bufSize);

  // open a file to dump header info into
  FILE *headerFile = NULL;
  headerFile = fopen (config.headerFile , "w");

  // and create a directory to put the events in if it doesn't exist
  err = OpenEventDir(config.eventDir);

  // start the data aquisition
  err = CAEN_DGTZ_SWStartAcquisition(devHandle);

  int iReadOut;
  uint32_t eventsAquired = 0;

  for(iReadOut = 0; iReadOut < config.nReadouts; iReadOut++){
    // open a file to dump the event intox
    sleep(1/config.polFreq);

    err = ReadoutEvents(devHandle, config.channel, 
			buffer,
			headerFile, config.eventDir, &eventsAquired);

    if(err){
      CleanUp(devHandle, buffer);
      return err;
    }
  }
  
  fclose(headerFile);
  CleanUp(devHandle, buffer);
  return 0;
}


SDQ_ERROR ReadoutEvents(int handle, uint32_t channel, char * buffer, FILE* headerFile, const char* eventDir, uint32_t* nEvents){
  // readout the data block
  uint32_t bufSize;
  CAEN_DGTZ_ErrorCode err = CAEN_DGTZ_ReadData(handle, CAEN_DGTZ_SLAVE_TERMINATED_READOUT_MBLT, 
					       buffer, &bufSize);

  if(err){
    printf("failed to read from device!\n");
    printf("%d\n", err);
    return err;
  }

  uint32_t eventsRead = 0;
  err = CAEN_DGTZ_GetNumEvents(handle, buffer, bufSize, &eventsRead); 
  printf("Aquired %d events\n", eventsRead);
   
    
  // now readout the events one by one, they are not in general the same size
  int iEv;
  char* eventPtr = NULL;
  CAEN_DGTZ_UINT16_EVENT_t *Evt = NULL;
  CAEN_DGTZ_EventInfo_t eventInfo;

  uint32_t lastTrig = 0;
  for(iEv = 0; iEv < eventsRead; iEv++){
    err = CAEN_DGTZ_GetEventInfo(handle,
				 buffer,
				 bufSize,
				 iEv,
				 &eventInfo,
				 &eventPtr
				 );
    
    if(err){
      printf("Failed to read event info!\n");
      return err;
    }

    fprintf(headerFile, "Event %d\n", iEv);
    fprintf(headerFile, "\ttrigger time: %d\n", eventInfo.TriggerTimeTag);
    fprintf(headerFile, "\tsince last trigger: %d\n", (eventInfo.TriggerTimeTag - lastTrig));
    fprintf(headerFile, "\n\n");
    
    lastTrig = eventInfo.TriggerTimeTag;
    err = CAEN_DGTZ_DecodeEvent(handle, eventPtr, (void**)&Evt);

    if(err){
      printf("Failed to decode event!\n");
      return err;
    }

    // open a file to save the event into
    char nameBuffer [50];
    sprintf (nameBuffer, "%s/event_%d.dat", eventDir, *nEvents);

    // look at the event itself 
    int nSamples = Evt->ChSize[channel];

    SaveEvent(nameBuffer, Evt->DataChannel[channel], nSamples);
    err = CAEN_DGTZ_FreeEvent(handle, (void**)&Evt);
    (*nEvents)++;

    if(err){
      printf("Failed to free event!\n");
      return err;
    }
    
  } // end of the event loop
  return 0;
}


SDQ_ERROR SaveEvent(const char* outFile, uint16_t* data, int nSamples){
  FILE *f;
  f = fopen(outFile, "w");
  int i = 0;
  for(; i < nSamples; i++)
    fprintf(f, "%d\n", data[i]);
  fclose(f);
  return 0;
}
