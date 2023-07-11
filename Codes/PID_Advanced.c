void Encoder_moveMm_Advanced(float dist, float accel = 1)
{
	float k = 1;

	if(dist < 0)
		k = -1;

	float initMm = EncoderToMm(getMotorEncoder(wheelL));

	Encoder_move[4].gearChangeValue = abs(dist / 2);

	float movedDistance = abs(EncoderToMm(getMotorEncoder(wheelL)) - initMm);

	int addition = 0;

	for(int i = 0; i < 4; i++)
		addition += Encoder_move[i].gearChangeValue;

	for(int i = 0; i < 5; i++)
	{
		Encoder_move[i].setpoint = getMotorEncoder(wheelR) - getMotorEncoder(wheelL);

		bool needToStop = false;

		Encoder_move[i].moveSpeed = abs(Encoder_move[i].moveSpeed) * k;

		PID_Encoder_On(Encoder_move[i], true);

		movedDistance = abs(EncoderToMm(getMotorEncoder(wheelL)) - initMm);

		while(movedDistance < Encoder_move[i].gearChangeValue * accel)
		{
			movedDistance = abs(EncoderToMm(getMotorEncoder(wheelL)) - initMm);

			if(movedDistance >= abs(dist / 2))
			{
				needToStop = true;
				break;
			}
		}

		if(needToStop)
		{
			break;
		}
	}

	Encoder_move[4].gearChangeValue -= addition;

	addition = 0;

	for(int i = 4; i >= 0; i--)
	{
		addition += Encoder_move[i].gearChangeValue;

		Encoder_move[i].moveSpeed = abs(Encoder_move[i].moveSpeed) * k;

		PID_Encoder_On(Encoder_move[i], true);

		movedDistance = abs(EncoderToMm(getMotorEncoder(wheelL)) - initMm);

		while(movedDistance < addition + abs(dist / 2))
		{
			movedDistance = abs(EncoderToMm(getMotorEncoder(wheelL)) - initMm);
		}

	}

	PID_Encoder_Off();

	for(int i = 0; i < 5; i++)
	{
		Encoder_move[i].moveSpeed = abs(Encoder_move[i].moveSpeed);
	}
}

void Gyro_Rotate_Advanced(float deg)
{
	float init = fusal_angle;

	float goal = init + deg;

	Gyro_Rotate[4].gearChangeValue = abs(deg / 2);

	float addition = 0;

	for(int i = 0; i < 4; i++)
		addition += Gyro_Rotate[i].gearChangeValue;

	float rotatedDeg;

	for(int i = 0; i < 5; i++)
	{
		bool needToStop = false;

		rotatedDeg = abs(fusal_angle - init);

		Gyro_Rotate[i].setpoint = goal;

		PID_Gyro_Start(Gyro_Rotate[i], on_always, 0);

		while(rotatedDeg < Gyro_Rotate[i].gearChangeValue)
		{
			rotatedDeg = abs(fusal_angle - init);

			if(rotatedDeg >= deg / 2)
			{
				needToStop = true;
				break;
			}
		}

		if(needToStop)
			break;
	}

	Gyro_Rotate[4].gearChangeValue -= addition;

	addition = 0;

	for(int i = 4; i >= 0; i--)
	{
		addition += Gyro_Rotate[i].gearChangeValue;

		PID_Gyro_Start(Gyro_Rotate[i], on_always, 0);

		rotatedDeg = abs(fusal_angle - init);

		while(rotatedDeg < addition + abs(deg / 2))
		{
			rotatedDeg = abs(fusal_angle - init);
		}
	}

	PID_Gyro_Off();
}
