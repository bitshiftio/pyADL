/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
** 
** THIS PROGRAM MAY DAMAGE YOUR VIDEO CARD, IF YOU APPLY NONSENSIAL VALUES.
**  e.g. INCREASING THE VOLTAGES AND FREQUENCIES IN CONJUNCTION WITH LOWERING THE
**  FAN SPEED IS NOT ADVISABLE!
**
** ALL ADL code has been taken from AMDOverdriveCtrl ( http://amdovdrvctrl.sourceforge.net/ )
** 
** AMDOverdriveCtrl Author: Thorsten Gilling (tgilling@web.de)
** 
** pyADL.cpp
** This is just a simple python extended library for AMD ADL
** Author: netxshare - http://www.bitshift.io
** 
** 1CWddfhXagPoWgzUCs7oVHFjwBmqbAoJRr
** -------------------------------------------------------------------------*/


I accept NO responsibility for any damage that may or may not be caused to your system by attempting an overclock, and this will also possibly void a manufacturer's warranty. Do this at your OWN RISK.


ADL SDK - http://developer.amd.com/Downloads/ADL_SDK_3.0.zip
Functions

pyADL.SetupADL(DeviceIndex) - This sets the GPU you wish to use.
pyADL.getTemp() - Returns the GPU Temp.
pyADL.getFanSpeed() - Returns the fan speed percent.
pyADL.getFanRPM() - Returns the fan RPMs.
pyADL.getCoreClockSpeed() - Returns Current Core Clock Speed.
pyADL.getMemoryClockSpeed() - Returns Current Memory Clock Speed.
pyADL.getVoltage() - Returns Current Voltage.

pyADL.setFanSpeed(Precent) - Sets The Fan Speed.
pyADL.setCoreClockSpeed(Level,Speed) - Sets Core Clock Speed. Level(0,1,2)
pyADL.setMemoryClockSpeed(Level,Speed) - Sets Memory Clock SPeed. Level(0,1,2)
pyADL.setVoltage(Level, Voltage) - Sets Voltage. Level(0,1,2)