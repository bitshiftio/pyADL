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
** pyADL.py
** This is just a simple python extended library for AMD ADL
** Author: netxshare - http://www.bitshift.io
** 
** 1CWddfhXagPoWgzUCs7oVHFjwBmqbAoJRr
** -------------------------------------------------------------------------*/
'''
import ADL

ADL.SetupADL(0)
print ADL.getGPULoad()
print ADL.getTemp()
print ADL.getFanSpeed()
print ADL.getFanRPM()
print ADL.getCoreClockSpeed()
print ADL.getMemoryClockSpeed()
print ADL.getVoltage()
ADL.setFanSpeed(75)
#ADL.setCoreClockSpeed(2,900)
ADL.SetupADL(5) # Switch to Second GPU on 6990
#ADL.setCoreClockSpeed(2,900)
print ADL.getTemp()
print ADL.getGPULoad()
#ADL.setMemoryClockSpeed(2,1000)
