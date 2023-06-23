void initializate()
{
	PID_init(Encoder_move[0], 0.1, 0, 0, 0.0004, 20, -20, 0, 5);
	PID_init(Encoder_move[1], 0.2, 0, 0.0003, 0.0004, 40, -40, 0, 15);
	PID_init(Encoder_move[2], 0.25, 0, 0.0007, 0.0004, 50, -50, 0, 30);
	PID_init(Encoder_move[3], 0.75, 0.0000001, 0.0011, 0.0004, 75, -75, 0, 50);
	PID_init(Encoder_move[4], 1, 0, 0.0016, 0.0004, 100, -100, 0, 70);

	PID_init(Gyro_Rotate[0], 0.05, 0, 0, 2, 20, -20, 0, 0);
	PID_init(Gyro_Rotate[1], 0.2, 0.0001, 0, 0.0004, 40, -40, 0, 0);
	PID_init(Gyro_Rotate[2], 0.25, 0, 0.08, 0.0004, 50, -50, 0, 0);
	PID_init(Gyro_Rotate[3], 0.75, 0, 0.0011, 0.0004, 75, -75, 0, 0);
	PID_init(Gyro_Rotate[4], 1, 0, 0.0016, 0.0004, 100, -100, 0, 0);

	Encoder_move[0].gearChangeValue = 10;
	Encoder_move[1].gearChangeValue = 30;
	Encoder_move[2].gearChangeValue = 75;
	Encoder_move[3].gearChangeValue = 150;

	for(int i = 0; i < 5; i++)
	{
		task_usage[i].use = none;
		task_prevUsage[i].use = none;

		Gyro_Rotate[i].acceptableRange = 0.2;
	}

	resetGyro(gyro);

	wait(500);

	Encoder_move[4].acceptableRange = 0;

	startTask(PID_LineFollower);
	startTask(PID_gyro);
	startTask(PID_Encoder);
	//startTask(receiveData);
	startTask(dataCalculation);
}
