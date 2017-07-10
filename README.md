SimpleDAQ
==========

Really basic DAQ for CAEN D5720 desktop digitizer and linux systems

Dependencies:
* Linux driver
* CAENVME
* CAENComm
* CAENDigitizer

Available [here](http://www.caen.it/csite/Function.jsp?parent=38&idfun=99) and [here](http://www.caen.it/csite/CaenProd.jsp?parent=14&idmod=624)

Get it with a download or a clone (remember the git submodule).

To compile:
`make`

You then need to write a configuration file with fields that match those in `config.example.ini`

Then to run:
`bin/simpledaq <path_to_configuration_file>`

This will produce two things with paths specified in the configuration file

1. A header file containing a list of entries, each containing a selection of the header info produced by the `CAEN` digitizer
1. A directory with a file for each event containing the digitized samples

`<eventDir>/event_0.dat` `<eventDir>/event_1.dat` ...

SimpleDAQ is about the simplest use of the (C) CAENDigitizer library imaginable: it internally triggers off one of its channels and reads out that same channel. The hardware and CAENDigitizer are by no means limited to this, documentation [available here](http://www.caen.it/csite/CaenProd.jsp?parent=38&idmod=717#).

Over USB, the digitizer is unable to annouce to its driver that it's time to readout events. Instead, it gradually fills up its internal buffer and the driver polls it triggering a readout of the events in the buffer up to a maximum number.

Note:
* the clock is 250MHz, so the samples are 4 ns apart
* the precision is 12bit, so the sample range is from 0 -> 4096

| Field Name | Description |
|---|---|
| maxEventsRead | Maximum number of events *on each readout* |
| recordLength | # samples read at each trigger |
| postTriggerSize | Position of trigger in event (%) 0 -> end, 100 -> beginning |
| channel | To trigger on and to read | 
| triggerPolarity | 0 -> upward going, 1 -> downward going |
| dcOffset | To add to the input signal to match the digitizers dynamic range (see below)|
| triggerTreshold | You guessed it/ adc counts |
| polFrequency | the frequency the computer asks the CAEN for available events |
| nReadouts | the number of times to ask the CAEN for data | 
| headerFile | path - to create and dump header info into (will overwrite) |
| eventDir | path to put the event files |
 
|DC Offset| Dynamic Range |
|---|---|
|`0x7FFF` |`-V/2` -> `V/2` | 
`0x0000`  | `-V` -> `0`| 
|`0xFFFF` | `0` -> `V`|

