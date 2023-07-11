void initializate()
{
	PID_init(Encoder_move[0], 0.1, 0, 0, 0.0004, 20, -20, 0, 5);
	PID_init(Encoder_move[1], 0.2, 0, 0.0003, 0.0004, 40, -40, 0, 15);
	PID_init(Encoder_move[2], 0.25, 0, 0.0007, 0.0004, 50, -50, 0, 30);
	PID_init(Encoder_move[3], 0.75, 0, 0.0011, 0.0004, 75, -75, 0, 50);
	PID_init(Encoder_move[4], 1, 0, 0, 0.0004, 100, -100, 0, 70);

	PID_init(LF[0], 1, 0, 0, 0.0004, 50, -50, 45, 45);
	PID_init(LF[1], 0.2, 0, 0.0003, 0.0004, 40, -40, 0, 15);
	PID_init(LF[2], 0.25, 0, 0.0007, 0.0004, 50, -50, 0, 30);
	PID_init(LF[3], 0.75, 0, 0.0011, 0.0004, 75, -75, 0, 50);
	PID_init(LF[4], 1, 0, 0, 0.0004, 100, -100, 0, 70);

	PID_init(Gyro_Rotate[0], 1, 0.003, 0, 0.0004, 15, -15, 0, 0);
	PID_init(Gyro_Rotate[1], 0.7, 0.0018, 0, 0.0004, 20, -20, 0, 0);
	PID_init(Gyro_Rotate[2], 1, 0.001, 0.1, 0.0004, 50, -50, 0, 0);
	PID_init(Gyro_Rotate[3], 0.75, 0.0005, 0.0011, 0.0004, 75, -75, 0, 0);
	PID_init(Gyro_Rotate[4], 1, 0.0006, 0.0016, 0.0004, 100, -100, 0, 0);

	PID_init(Fuse_Rotate[0], 1, 0.003, 0, 0.0004, 15, -15, 0, 0);
	PID_init(Fuse_Rotate[1], 0.7, 0.0018, 0, 0.0004, 20, -20, 0, 0);
	PID_init(Fuse_Rotate[2], 1, 0.001, 0.1, 0.0004, 50, -50, 0, 0);
	PID_init(Fuse_Rotate[3], 0.75, 0.0005, 0.0011, 0.0004, 75, -75, 0, 0);
	PID_init(Fuse_Rotate[4], 1, 0.0006, 0.0016, 0.0004, 100, -100, 0, 0);

	Encoder_move[0].gearChangeValue = 15;
	Encoder_move[1].gearChangeValue = 45;
	Encoder_move[2].gearChangeValue = 90;
	Encoder_move[3].gearChangeValue = 180;

	Gyro_Rotate[0].gearChangeValue = 15;
	Gyro_Rotate[1].gearChangeValue = 45;
	Gyro_Rotate[2].gearChangeValue = 90;
	Gyro_Rotate[3].gearChangeValue = 180;

	Fuse_Rotate[0].fusingAlpha_OneSided = 0.48;
	Fuse_Rotate[0].fusingAlpha_TwoSided = 0.4775;

	Fuse_Rotate[1].fusingAlpha_OneSided = 0.48;
	Fuse_Rotate[1].fusingAlpha_TwoSided = 0.4909;

	Fuse_Rotate[2].fusingAlpha_OneSided = 0.491;
	Fuse_Rotate[2].fusingAlpha_TwoSided = 0.495;

	Fuse_Rotate[3].fusingAlpha_OneSided = 0.478;
	Fuse_Rotate[3].fusingAlpha_TwoSided = 0.4915;

	Fuse_Rotate[4].fusingAlpha_OneSided = 0.478;
	Fuse_Rotate[4].fusingAlpha_TwoSided = 0.4915;

	for(int i = 0; i < 5; i++)
	{
		task_usage[i].use = none;
		task_prevUsage[i].use = none;

		Gyro_Rotate[i].acceptableRange = 0.1;
		Fuse_Rotate[i].acceptableRange = 0.1;
	}

	resetGyro(gyro);

	wait(500);

	Encoder_move[4].acceptableRange = 0;

	tasks[3] = &Fuse_Rotate[0];

	startTask(PID_LineFollower);
	startTask(PID_gyro);
	startTask(PID_Encoder);
	startTask(PID_Fuse);
	startTask(dataCalculation);
}
