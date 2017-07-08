Really basic DAQ for CAEN digitizer D720

Dependencies:
* Linux driver
* CAENVME
* CAENComm
* CAENDigitizer

To compile:
`make`

You then need to write a configuration file with fields that match those in `config.example.ini`

Then to run:
`bin/simpledaq <path_to_configuration_file>`