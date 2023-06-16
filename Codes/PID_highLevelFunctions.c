int grabHeight = 80;
void PID_FollowLine_Until_Reflected(PID* pid, float reflection)
{
	PID_LineFollower_On_ForTime(pid, pid->lineCorrectionTime);

	playSound(soundLowBuzz);

	PID_LineFollower_On_Until_Reflected(pid, reflection);
}

void PID_FollowLine_AndTurn(PID* pid_lineFollower, PID* gyro_rotate, PID* gyro_move, float reflection, float turn_angle, int mode)
{
	PID_FollowLine_Until_Reflected(pid_lineFollower, reflection);

	playSound(soundBlip);

	gyro_move->setpoint = getGyroDegrees(gyro);

	if(mode == 1)
	{
		PID_Gyro_On_Until_Encoder(Gyro_move, getMotorEncoder(wheelL) - MmToEncoder(22.5));
	}
	else
	{
		PID_Gyro_On_Until_Encoder(Gyro_move, getMotorEncoder(wheelL) - MmToEncoder(26.5));
	}
	while(task_usage[1].use != none){}

	playSound(soundBlip);

	PID_Gyro_Rotate(gyro_rotate, turn_angle);

	while(task_usage[1].use != none){}
}
