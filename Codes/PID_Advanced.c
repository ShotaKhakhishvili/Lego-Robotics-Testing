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
		bool needToStop = false;

		Encoder_move[i].moveSpeed = abs(Encoder_move[i].moveSpeed) * k;

		PID_Encoder_On(Encoder_move[i], true);

		movedDistance = abs(EncoderToMm(getMotorEncoder(wheelL)) - initMm);

		while(movedDistance < Encoder_move[i].gearChangeValue * accel)
		{
			movedDistance = abs(EncoderToMm(getMotorEncoder(wheelL)) - initMm);

			AAAAAA = movedDistance;

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

	//PID_Encoder_Off();

	//return;

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

			AAAAAA = movedDistance;
		}

	}

	PID_Encoder_Off();

	for(int i = 0; i < 5; i++)
	{
		Encoder_move[i].moveSpeed = abs(Encoder_move[i].moveSpeed);
	}
}

//void Encoder_moveMm_Advanced(float deg, float accel = 1)
//{
//	float initDeg = getGyroDegrees(gyro);

//	Encoder_move[4].gearChangeValue = deg / 2 ;

//	float deltaDegree = abs(EncoderToMm(getMotorEncoder(wheelL)) - initDeg);

//	float movedDist[5];

//	for(int i = 0; i < 5; i++)
//	{
//		bool needToStop = false;

//		Encoder_move[i].moveSpeed = abs(Encoder_move[i].moveSpeed) * k;

//		PID_Encoder_On(Encoder_move[i]);

//		while(movedDistance < Encoder_move[i].gearChangeValue * accel)
//		{
//			movedDistance = abs(EncoderToMm(getMotorEncoder(wheelL)) - initMm);

//			if(movedDistance >= dist / 2)
//			{
//				needToStop = true;
//				break;
//			}
//		}

//		if(i == 0)
//			movedDist[i] = movedDistance;
//		else
//			movedDist[i] = movedDistance - movedDist[i-1];

//		if(needToStop)
//			break;
//	}

//	for(int i = 4; i >= 0; i--)
//	{
//		Encoder_move[i].moveSpeed = abs(Encoder_move[i].moveSpeed) * k;

//		PID_Encoder_On(Encoder_move[i]);

//		while(movedDistance -  dist / 2 < movedDist[i])
//		{
//			movedDistance = abs(EncoderToMm(getMotorEncoder(wheelL)) - initMm);
//		}
//	}

//	PID_Encoder_Off();

//	for(int i = 0; i < 5; i++)
//	{
//		Encoder_move[i].moveSpeed = abs(Encoder_move[i].moveSpeed);
//	}
//}
