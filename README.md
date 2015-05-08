# PFillerFirmware
PIC firmware and schematic for a vibratory feeder-based net-weight filling machine controller

Development platform: MPLab
Toolchain: C18
Target MCU: 18F25K50

Feeder controller used: Rodix FC-40 Plus Series, though any controller that accepts a 0-5v control input should be usable
Vibratory Feeder used: Eriez Model 6C 
Scale used: AWS PN-Series with serial interface

Diptrace schematic and PCB board are located in the Board directory.

General information:
Basic use, use the interface button to select the type item to fill, and the weight to fill each cycle.  Press the foot pedal to
start the fill cycle and to pause the fill cycle.

Firmware contains a table specifiying weight/feeder speed combinations for different substances that will be used for the filling 
machine burned directly into flash.  Each entry in the table represents the speed that the feeder should operate when there is 
the specified weight left to fill.  The different substances in this table can then be selected via the interface during the 
operation of the feeder.  To add, modify, rename, or otherwise customize the feed rates for the substances in your project modify
the table values in the: Make_WeightSpeedEntries function in PFiller_SpeedTable.c .   This table can then be burned into flash 
next time the firmware is run by uncommenting this function in main.


