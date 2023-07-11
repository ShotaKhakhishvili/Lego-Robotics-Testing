/*
	Fuse-s PID-is Chartva Ragac Droit

	@param [PID*] pid							PID-is Pointeri Romelsac Chavrtavt Ragac Droit
	@param [float] time						Dro Ramden Xnit Chavrtavt
*/
void PID_Fuse_On_ForTime(PID* pid, float time, bool parallel = false)
{
	PID_Fuse_Start(pid, forTime, time); // Chavrtavt PID-s

	if(!parallel)
	{
		while(task_usage[3].use != none){}
	}
}

/*
	Fuse-s PID-s Chartva Sanam Ragac Konkretuli Kutxit Ar Shevtrialdebit

	@param [PID*] pid 						PID-is Pointer-i Romelsac Chavrtavt Sanam Sasurvel Mandzilze Ar Mivalt
	@param [float] angle		 			Kutxe Romlitac Unda Shevtrialdet
*/
void PID_Fuse_Rotate(PID* pid, float angle, bool parallel = false)
{
	float initAngle = fusal_angle; // Vinaxavt Sawyis Kutxes

	pid->setpoint = initAngle + angle; // Setpointad Vutitebt Sawyiss + Sasurveli Shemotrialebis Kutxes

	PID_Fuse_Start(pid, on_untilDone, 0); // Chavrtavt PID-s

	if(!parallel)
	{
		while(task_usage[3].use != none){}
	}
}


/*
	Fuse-s PID-s Chartva Sanam Color Sensor-it Sasurvel Reflected-s Ar Mivigebt

	@param [PID*] pid 						PID-is Pointer-i Romelsac Chavrtavt Sanam Sasurvel Mandzilze Ar Mivalt
	@param [float] _setpoint 			Sasurveli LineFollower-is Color Sensor-is Mnishvneloba
*/
void PID_Fuse_On_Until_Reflected(PID* pid, float _setpoint, bool parallel = false)
{
	if(_setpoint >= getColorReflected(col1))
	{
		PID_Fuse_Start(pid, untilReflected_high, _setpoint);
	}
	else
	{
		PID_Fuse_Start(pid, untilReflected_low, _setpoint);
	}

	if(!parallel)
	{
		while(task_usage[3].use != none){}
	}
}

void PID_Fuse_On_Until_Encoder(PID* pid, float _setpoint, bool parallel = false)
{
	if(_setpoint >= getMotorEncoder(wheelL))
	{
		PID_Fuse_Start(pid, untilEncoder_high, _setpoint);
	}
	else
	{
		PID_Fuse_Start(pid, untilEncoder_low, _setpoint);
	}

	if(!parallel)
	{
		while(task_usage[3].use != none){}
	}
}

void PID_Fuse_On(PID* pid, bool parallel = false)
{
	PID_Fuse_Start(pid, on_always, 0); // Chavrtavt PID-s

	if(!parallel)
	{
		while(task_usage[3].use != none){}
	}
}

void PID_Fuse_Off()
{
	PID_Fuse_Start(tasks[3], none, 0);

	setMotorSpeed(wheelL, 0);
	setMotorSpeed(wheelR, 0);
}
