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

Put the ADL SDK in ./ADL_SDK

Functions

ADL.SetupADL(DeviceIndex) - This sets the GPU you wish to use.
ADL.getTemp() - Returns the GPU Temp.
ADL.getGPULoad() - Returns the current gpu load percent.
ADL.getFanSpeed() - Returns the fan speed percent.
ADL.getFanRPM() - Returns the fan RPMs.
ADL.getCoreClockSpeed() - Returns Current Core Clock Speed.
ADL.getMemoryClockSpeed() - Returns Current Memory Clock Speed.
ADL.getVoltage() - Returns Current Voltage.

ADL.setFanSpeed(Precent) - Sets The Fan Speed.
ADL.setCoreClockSpeed(Level,Speed) - Sets Core Clock Speed. Level(0,1,2)
ADL.setMemoryClockSpeed(Level,Speed) - Sets Memory Clock Speed. Level(0,1,2)
ADL.setVoltage(Level, Voltage) - Sets Voltage. Level(0,1,2)