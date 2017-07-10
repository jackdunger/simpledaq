#include <config.h>
#include <acquisition.h>
#include <CAENDigitizer.h>
#include <stdio.h>
#include <err.h>

int main(int argc, char* argv[]){
  if (argc != 2){
    printf("Usage:\n simpledaq <path_to_config_file>\n");
    return 1;
  }

  // parse and log the configuration file
  SDQ_Config_t config;
  SDQ_ERROR err = SDQ_ParseConfig(argv[1], &config);
  if(err){
    printf("Execution failed with: %s\n" , error_msg(err));
    return err;
  }


  SDQ_PrintConfig(config);

  // run the experiment
  err = SDQ_RunAcquisition(config);
  
  if(err){
    printf("Execution failed with: %s\n" , error_msg(err));
    return err;
  }


  // all good
  return err;
}
