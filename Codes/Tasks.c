task Cimcimi()
{
	while(1)
	{
	 	wait(50);

		//getColorAmbient(color2); // Gadavrtavt Ambient Mode-ze

		wait(50);

		//getColorName(color2);

		wait(50);

	 	//checkedColor = getColorName(color2);

	 	checkStatus = !checkStatus;
	}
}

task receiveData()
{
	while(1)
	{
		int startTime = time1(T1);

		//gyro = getGyroDegrees(sensor_gyro);
		//encoder_WL = getMotorEncoder(wheelL);
		//encoder_WR = getMotorEncoder(wheelR);
		//reflected_col1 = getColorReflected(sensor_col1);
		//teflected_col2 = getColorReflected(sensor_col2);

		while(time1(T1) < startTime + sampleTime_receiveData){}

	}
}

task dataCalculation()
{
	startTask(receiveData);

	while(true) // run until some condition is met
	{
		float startTime = time1(T1);

		gyro_angle = getGyroDegrees(gyro);
		gyro_curr_mes = getGyroRate(gyro);
		encoder_WL = getMotorEncoder(wheelL);
		encoder_WR = getMotorEncoder(wheelR);

		currEncoderWl = EncoderToMm(encoder_WL);
		currEncoderWr = EncoderToMm(encoder_WR);

		float deltaA = -(currEncoderWl - prevEncoderWl) * 180 / (PI * disBetweenWheels);
		float deltaB = (currEncoderWr - prevEncoderWr) * 180 / (PI * disBetweenWheels);

		prevEncoderWl = currEncoderWl;
		prevEncoderWr = currEncoderWr;

		// fusing stuff

		encoder_curr_mes = (deltaA + deltaB) * (1000 / sampleTime_encoderSpeed);

		curr_fusal_velocity = Fusion_Gyro_Encoders();

		encoder_prev_filtered = encoder_curr_filtered;

		gyro_prev_filtered = gyro_curr_filtered;
		gyro_prev_mes = gyro_curr_mes;

		fusal_angle += (sampleTime_encoderSpeed / 1000) * (curr_fusal_velocity + prev_fusal_velocity);

		prev_fusal_velocity = curr_fusal_velocity;

		// no fusing stuff no more

		while(time1(T1) < startTime + sampleTime_encoderSpeed){}
	}
}
