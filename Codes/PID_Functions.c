/*
	// ROBOTI UNDA IYOS GACHEREBULI AM PUNQSIIC GAMOYENEBAMDE //

	Abrunebs Color Checker-i Sensoris Mnishvnelobas Upro Zustad

	return Sensoris Mnishvneloba
*/
int ColorCheck()
{
	bool currentStatus = checkStatus;

	wait(500);

	float cntGreen = 0;
	float checkAmount = 1;
	float requiredPercentage = 0.5;

	for(int i = 0; i < checkAmount; i++)
	{
		while(currentStatus == checkStatus){}

		if(checkedColor == 3)
		{
			cntGreen++;
		}

		currentStatus = checkStatus;
	}

	bool ans = ((cntGreen / checkAmount) >= requiredPercentage);

	if(ans)
	{
		return 3;
	}

	return 2;
}

void simpleMoveMm(float Mm, int speed = 20)
{
	float encoderVal = MmToEncoder(Mm);

	float targetR = getMotorEncoder(wheelR) + encoderVal;
	float targetL = getMotorEncoder(wheelL) - encoderVal;

	bool doneR = false, doneL = false;

	setMotorSpeed(wheelR, 30);
	setMotorSpeed(wheelL, 30);

	while(!doneR || !doneL)
	{
		if(!doneL)
			doneL = inRange(getMotorEncoder(wheelL), targetL, speed);

		if(!doneR)
			doneR = inRange(getMotorEncoder(wheelR), targetR, speed);

		if(doneL)
		{
			setMotorSpeed(wheelL, 0);
		}
		if(doneR)
		{
			setMotorSpeed(wheelR, 0);
		}

	}
	playSound(soundBlip);
}

void Gyro_moveMm(PID* pid, float Mm, float speed = 0)
{
	pid->setpoint = getGyroDegrees(gyro);

	if(speed == 0)
	{
		if(Mm > 0)
		{
			pid->moveSpeed = abs(pid->moveSpeed);
		}
		else
		{
			pid->moveSpeed = -abs(pid->moveSpeed);
		}
	}
	else
	{
		if(Mm > 0)
		{
			pid->moveSpeed = abs(speed);
		}
		else
		{
			pid->moveSpeed = -abs(speed);
		}
	}

	wait(10);

	PID_Gyro_On_Until_Encoder(pid, getMotorEncoder(wheelL) - MmToEncoder(Mm));

	while(task_usage[1].use != none){}
}

void Gyro_moveForTime(PID* pid, float time, float speed = 0)
{
	pid->setpoint = getGyroDegrees(gyro);

	if(speed != 0)
		pid->moveSpeed = speed;

	wait(10);

	PID_Gyro_On_ForTime(pid, time);
}

void Gyro_moveUntilReflected(PID* pid, float reflection, float speed = 0)
{
	pid->setpoint = getGyroDegrees(gyro);

	if(speed != 0)
		pid->moveSpeed = speed;

	wait(10);

	PID_Gyro_On_Until_Reflected(pid, reflection);
}

void Encoder_moveMm(PID* pid, float Mm, float speed = 0)
{
	pid->setpoint = getMotorEncoder(wheelR) + getMotorEncoder(wheelL);

	if(speed == 0)
	{
		if(Mm > 0)
		{
			pid->moveSpeed = abs(pid->moveSpeed);
		}
		else
		{
			pid->moveSpeed = -abs(pid->moveSpeed);
		}
	}
	else
	{
		if(Mm > 0)
		{
			pid->moveSpeed = abs(speed);
		}
		else
		{
			pid->moveSpeed = -abs(speed);
		}
	}

	wait(10);

	PID_Encoder_On_Until_Encoder(pid, getMotorEncoder(wheelL) + MmToEncoder(Mm));

	while(task_usage[2].use != none){}
}

void Encoder_moveForTime(PID* pid, float time, float speed = 0)
{
	pid->setpoint = getMotorEncoder(wheelR) + getMotorEncoder(wheelL);

	if(speed != 0)
		pid->moveSpeed = speed;

	wait(10);

	PID_Encoder_On_ForTime(pid, time);
}

void Encoder_moveUntilReflected(PID* pid, float reflection, float speed = 0)
{
	pid->setpoint = getMotorEncoder(wheelR) + getMotorEncoder(wheelL);

	if(speed != 0)
		pid->moveSpeed = speed;

	wait(10);

	PID_Encoder_On_Until_Reflected(pid, reflection);
}

float filter_highPass(float prev_filtered, float curr_mes, float prev_mes, float timestep_s, float cuttof_freq)
{
	float alpha = 1 - 1 / (1 + 2 * PI * cuttof_freq * timestep_s);

	return (1 - alpha) * prev_filtered + (1 - alpha) * (curr_mes - prev_mes);
}

float filter_lowPass(float prev_filtered, float curr_mes, float timestep_s, float cuttof_freq)
{
	float alpha = 1 / (1 + 2 * PI * cuttof_freq * timestep_s);

	return alpha * prev_filtered + (1 - alpha) * curr_mes;
}

float filter_complementary(float filtered_a, float filtered_b, float alpha)
{
	return alpha * filtered_a + (1 - alpha) * filtered_b;
}

float Fusion_Gyro_Encoders()
{
	gyro_curr_filtered = filter_highPass(gyro_prev_filtered, gyro_curr_mes, gyro_prev_mes, sampleTime_dataCalculation / 1000, 100);

	gyro_prev_filtered = gyro_curr_filtered;
	gyro_prev_mes = gyro_curr_mes;

	encoder_curr_filtered = filter_lowPass(encoder_prev_filtered, encoder_curr_mes, sampleTime_dataCalculation / 1000, 100);

	encoder_prev_filtered = encoder_curr_filtered;

	if(tasks[3]->oneSided)
		return filter_complementary(gyro_curr_filtered, encoder_curr_filtered, tasks[3]->fusingAlpha_OneSided);

	else
		return filter_complementary(gyro_curr_filtered, encoder_curr_filtered, tasks[3]->fusingAlpha_TwoSided);
}
