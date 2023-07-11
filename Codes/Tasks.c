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

void receiveData()
{
	gyro_angle = getGyroDegrees(gyro);
	gyro_curr_mes = getGyroRate(gyro);
	encoder_WL = getMotorEncoder(wheelL);
	encoder_WR = getMotorEncoder(wheelR);
}

task dataCalculation()
{
	while(true) // run until some condition is met
	{
		float startTime = time1(T1);

		receiveData();

		currEncoderWl = EncoderToMm(encoder_WL);
		currEncoderWr = EncoderToMm(encoder_WR);

		float deltaA = -(currEncoderWl - prevEncoderWl) * 180 / (PI * disBetweenWheels);
		float deltaB = (currEncoderWr - prevEncoderWr) * 180 / (PI * disBetweenWheels);

		prevEncoderWl = currEncoderWl;
		prevEncoderWr = currEncoderWr;

		// fusing stuff

		encoder_curr_mes = (deltaA + deltaB) * (1000 / sampleTime_dataCalculation);

		curr_fusal_velocity = Fusion_Gyro_Encoders();

		encoder_prev_filtered = encoder_curr_filtered;

		gyro_prev_filtered = gyro_curr_filtered;
		gyro_prev_mes = gyro_curr_mes;
		gyro_prev = gyro_angle;

		fusal_angle += (sampleTime_dataCalculation / 1000) * (curr_fusal_velocity + prev_fusal_velocity);

		prev_fusal_velocity = curr_fusal_velocity;

		// no fusing stuff no more

		while(time1(T1) < startTime + sampleTime_dataCalculation){}
	}
}
