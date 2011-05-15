'''
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
'''
import pyADL

pyADL.SetupADL(0)
print pyADL.getTemp()
print pyADL.getFanSpeed()
print pyADL.getFanRPM()
print pyADL.getCoreClockSpeed()
print pyADL.getMemoryClockSpeed()
print pyADL.getVoltage()
pyADL.setFanSpeed(75)
#pyADL.setCoreClockSpeed(2,900)
pyADL.SetupADL(5) # Switch to Second GPU on 6990
#pyADL.setCoreClockSpeed(2,900)
print pyADL.getTemp()
#pyADL.setMemoryClockSpeed(2,1000)
