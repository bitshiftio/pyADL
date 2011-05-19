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


#include <Python.h>
#include "adl.h"

ADL* adl;
long int GpuIndex = 0;

static PyObject *SetupADL(PyObject *self, PyObject *args)
{
	adl = ADL::Instance();
	
	 

	if(!PyArg_ParseTuple(args, "i", &GpuIndex))
		return NULL;

	if (adl == NULL)
	{

		return Py_BuildValue("s","Unable to initialize AMD ADL Library.");
	}
	
	adl->SetGPUIndex(&GpuIndex);

	Py_INCREF(Py_None);
	return Py_None;

}

static PyObject *getGPULoad(PyObject *self, PyObject *noarg)
{
	
	PyObject *Results;

	if (adl->GetSupportedFeatures() & ADL::FEAT_GET_ACTIVITY)
	{
		Results = Py_BuildValue("i", adl->mODActivity.iActivityPercent);
		return Results;
	}
	else
	{
		Results = Py_BuildValue("s", "getGPULoad() Failed.");
		return Results;
	}
}

static PyObject *getTemp(PyObject *self, PyObject *noarg)
{
	PyObject *Results;
	if (adl->GetSupportedFeatures() & ADL::FEAT_GET_TEMPERATURE)
	{
		Results = Py_BuildValue("f", (float)adl->mTemperature.iTemperature/1000.0);
		return Results;
	}
	else
	{

		Results =  Py_BuildValue("s", "getTemp() Failed.");
		return Results;
	}

}

static PyObject *getFanSpeed(PyObject *self, PyObject *noarg)
{
	PyObject *Results;
	if ((adl->GetSupportedFeatures() & ADL::FEAT_GET_FANSPEED_INFO) && (adl->GetSupportedFeatures() & ADL::FEAT_GET_FANSPEED))
	{
		Results = Py_BuildValue("i", adl->mCurrentFanSpeed.iFanSpeed * 100 / adl->mFanSpeedInfo.iMaxRPM);
		return Results;
	}
	else
	{

		Results = Py_BuildValue("s", "getFanSpeed() Failed.");
		return Results;
	}

}

static PyObject *getFanRPM(PyObject *self, PyObject *noarg)
{
	PyObject *Results;

	if ((adl->GetSupportedFeatures() & ADL::FEAT_GET_FANSPEED_INFO) && (adl->GetSupportedFeatures() & ADL::FEAT_GET_FANSPEED))
	{
		Results = Py_BuildValue("i", adl->mCurrentFanSpeed.iFanSpeed);
		return Results;
	}
	else
	{

		Results = Py_BuildValue("s", "getFanRPM() Failed.");
		return Results;
	}

}

static PyObject *getCoreClockSpeed(PyObject *self, PyObject *noarg)
{
	
	PyObject *Results;

	if (adl->GetSupportedFeatures() & ADL::FEAT_GET_OD_PARAMETERS)
	{
		Results =  Py_BuildValue("i", adl->mpODPerformanceLevels->aLevels[adl->mODActivity.iCurrentPerformanceLevel].iEngineClock/100);
		return Results;
	}
	else
	{

		Results = Py_BuildValue("s", "getCoreClockSpeed() Failed.");
		return Results;
	}
}

static PyObject *getMemoryClockSpeed(PyObject *self, PyObject *noarg)
{

	PyObject *Results;

	if (adl->GetSupportedFeatures() & ADL::FEAT_GET_OD_PARAMETERS)
	{
		Results = Py_BuildValue("i", adl->mpODPerformanceLevels->aLevels[adl->mODActivity.iCurrentPerformanceLevel].iMemoryClock/100);
		return Results;
	}
	else
	{
		Results = Py_BuildValue("s", "getMemoryClockSpeed() Failed.");
		return Results;
	}
}

static PyObject *getVoltage(PyObject *self, PyObject *noarg)
{

	PyObject *Results;
	if (adl->GetSupportedFeatures() & ADL::FEAT_GET_OD_PARAMETERS)
	{
		Results = Py_BuildValue("f", (float)adl->mpODPerformanceLevels->aLevels[adl->mODActivity.iCurrentPerformanceLevel].iVddc/1000.0);
		return Results;
	}
	else
	{
		Results = Py_BuildValue("s", "getVoltage() Failed.");
		return Results;
	}

}

static PyObject *setFanSpeed(PyObject *self, PyObject *args)
{
	int percent;

	if(!PyArg_ParseTuple(args, "i", &percent))
		return NULL;

	if (adl->GetSupportedFeatures() & ADL::FEAT_GET_FANSPEED)
	{
		ADLFanSpeedValue speed_value;

		speed_value.iSize = sizeof(ADLFanSpeedValue);
		speed_value.iFlags = ADL_DL_FANCTRL_FLAG_USER_DEFINED_SPEED;
		speed_value.iFanSpeed = percent;
		speed_value.iSpeedType = ADL_DL_FANCTRL_SPEED_TYPE_PERCENT;

		if(SAVE_CALL(adl->ADL_Overdrive5_FanSpeed_Set)(adl->GetGPUIndex(), 0, &speed_value) != ADL_OK)
		{
			Py_INCREF(Py_False);
			return Py_False;
		}
		else
		{
			ACT_LOG("Fan speed set to " << percent << "%");
			Py_INCREF(Py_True);
			return Py_True;
		}

	}

	Py_INCREF(Py_False);
	return Py_False;

		
}


static PyObject *setCoreClockSpeed(PyObject *self, PyObject *args)
{
	int Level,CoreSpeed;
	
	if(!PyArg_ParseTuple(args, "ii", &Level, &CoreSpeed))
		return NULL;

	if((adl->GetSupportedFeatures() & ADL::FEAT_GET_OD_PARAMETERS) && (adl->GetSupportedFeatures() & ADL::FEAT_GET_OD_PERF_LEVELS))
	{
		ADLODParameters para;
		ADLODPerformanceLevels* levels;

		ADL* adl = ADL::Instance();

		if(SAVE_CALL(adl->ADL_Overdrive5_ODParameters_Get)(adl->GetGPUIndex(), &para) == ADL_OK)
		{
			int perf_level_size = sizeof(ADLODPerformanceLevels) + sizeof(ADLODPerformanceLevel) * (para.iNumberOfPerformanceLevels - 1);
			levels = (ADLODPerformanceLevels*)malloc(perf_level_size);
			levels->iSize = perf_level_size;

			if(SAVE_CALL(adl->ADL_Overdrive5_ODPerformanceLevels_Get)(adl->GetGPUIndex(), 0, levels) == ADL_OK)
			{
				levels->aLevels[Level].iEngineClock = CoreSpeed * 100;
				ACT_LOG("SetOverdriveValues: Level " << Level << ": Core Clock: " << CoreSpeed << "MHz");
				
			}

			if(SAVE_CALL(adl->ADL_Overdrive5_ODPerformanceLevels_Set)(adl->GetGPUIndex(), levels) != ADL_OK)
			{
				Py_INCREF(Py_False);
				return Py_False;
			}

			free(levels);
			levels = NULL;

			Py_INCREF(Py_True);
			return Py_True;
		}
		Py_INCREF(Py_False);
		return Py_False;
	}
	Py_INCREF(Py_False);
	return Py_False;
}

static PyObject *setMemoryClockSpeed(PyObject *self, PyObject *args)
{
	int Level,CoreSpeed;

	if(!PyArg_ParseTuple(args, "ii", &Level, &CoreSpeed))
		return NULL;

	if((adl->GetSupportedFeatures() & ADL::FEAT_GET_OD_PARAMETERS) && (adl->GetSupportedFeatures() & ADL::FEAT_GET_OD_PERF_LEVELS))
	{
		ADLODParameters para;
		ADLODPerformanceLevels* levels;

		ADL* adl = ADL::Instance();

		if(SAVE_CALL(adl->ADL_Overdrive5_ODParameters_Get)(adl->GetGPUIndex(), &para) == ADL_OK)
		{
			int perf_level_size = sizeof(ADLODPerformanceLevels) + sizeof(ADLODPerformanceLevel) * (para.iNumberOfPerformanceLevels - 1);
			levels = (ADLODPerformanceLevels*)malloc(perf_level_size);
			levels->iSize = perf_level_size;

			if(SAVE_CALL(adl->ADL_Overdrive5_ODPerformanceLevels_Get)(adl->GetGPUIndex(), 0, levels) == ADL_OK)
			{
				levels->aLevels[Level].iMemoryClock = CoreSpeed * 100;
				ACT_LOG("SetOverdriveValues: Level " << Level << ": Memory Clock: " << CoreSpeed << "MHz");

			}

			if(SAVE_CALL(adl->ADL_Overdrive5_ODPerformanceLevels_Set)(adl->GetGPUIndex(), levels) != ADL_OK)
			{
				Py_INCREF(Py_False);
				return Py_False;
			}

			free(levels);
			levels = NULL;

			Py_INCREF(Py_True);
			return Py_True;
		}
		Py_INCREF(Py_False);
		return Py_False;
	}
	Py_INCREF(Py_False);
	return Py_False;
}

static PyObject *setVoltage(PyObject *self, PyObject *args)
{
	int Level,Voltage;

	if(!PyArg_ParseTuple(args, "ii", &Level, &Voltage))
		return NULL;

	if((adl->GetSupportedFeatures() & ADL::FEAT_GET_OD_PARAMETERS) && (adl->GetSupportedFeatures() & ADL::FEAT_GET_OD_PERF_LEVELS))
	{
		ADLODParameters para;
		ADLODPerformanceLevels* levels;

		ADL* adl = ADL::Instance();

		if(SAVE_CALL(adl->ADL_Overdrive5_ODParameters_Get)(adl->GetGPUIndex(), &para) == ADL_OK)
		{
			int perf_level_size = sizeof(ADLODPerformanceLevels) + sizeof(ADLODPerformanceLevel) * (para.iNumberOfPerformanceLevels - 1);
			levels = (ADLODPerformanceLevels*)malloc(perf_level_size);
			levels->iSize = perf_level_size;

			if(SAVE_CALL(adl->ADL_Overdrive5_ODPerformanceLevels_Get)(adl->GetGPUIndex(), 0, levels) == ADL_OK)
			{
				levels->aLevels[Level].iVddc = Voltage;
				ACT_LOG("SetOverdriveValues: Level " << Level << ": Voltage: " << Voltage << " V");

			}

			if(SAVE_CALL(adl->ADL_Overdrive5_ODPerformanceLevels_Set)(adl->GetGPUIndex(), levels) != ADL_OK)
			{
				Py_INCREF(Py_False);
				return Py_False;
			}

			free(levels);
			levels = NULL;

			Py_INCREF(Py_True);
			return Py_True;
		}
		Py_INCREF(Py_False);
		return Py_False;
	}
	Py_INCREF(Py_False);
	return Py_False;
}



static PyMethodDef ADL_Methods[] = {
	
	{"SetupADL", SetupADL, METH_VARARGS, "Initialize ADL."},
	{"getGPULoad", getGPULoad, METH_NOARGS, "Returns Current GPU Load."},
	{"getTemp",  getTemp, METH_NOARGS, "Returns GPU Temperature."},
	{"getFanSpeed", getFanSpeed, METH_NOARGS, "Returns Fan Speed."},
	{"getFanRPM", getFanRPM, METH_NOARGS, "Returns Current Fan RPM."},
	{"getCoreClockSpeed", getCoreClockSpeed, METH_NOARGS, "Returns Current Core Clock Speed."},
	{"getMemoryClockSpeed", getMemoryClockSpeed, METH_NOARGS, "Returns Current Memory Clock Speed."},
	{"getVoltage", getVoltage, METH_NOARGS, "Returns Current Voltage."},
	{"setFanSpeed", setFanSpeed, METH_VARARGS, "Sets The Fan Speed."},
	{"setCoreClockSpeed", setCoreClockSpeed, METH_VARARGS, "Sets The Core Clock Speed."},
	{"setMemoryClockSpeed", setMemoryClockSpeed, METH_VARARGS, "Sets The Memory Clock Speed."},
	{"setVoltage", setVoltage, METH_VARARGS, "Sets The GPU Voltage."},
	{NULL, NULL, 0, NULL}
};


PyMODINIT_FUNC initADL(void)
{
	
	PyObject *m;

	m = Py_InitModule("ADL", ADL_Methods);
	if (m == NULL)
		return;

}


