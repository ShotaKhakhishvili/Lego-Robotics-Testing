#pragma config(Sensor, S1,     color1,         sensorEV3_Ultrasonic)
#pragma config(Sensor, S2,     gyro,           sensorEV3_Gyro)
#pragma config(Sensor, S4,     usonic,         sensorEV3_Color)
#pragma config(Motor,  motorA,          claw,          tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorB,          wheelR,        tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorC,          wheelL,        tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorD,          hand,          tmotorEV3_Large, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// color1 - LineFollower-is Sensor-i
// color2 - ColorCheck-is Sensor-i

//float lineCorrectionTime = 1000;

int AAAA;
int AAAAAA;

//int cBlack = 8;
//int cDarkBlue = 11;
//int cBlue = 15;
//int cWhite = 76;

int checkedColor = -1;
bool checkStatus = false;

#include "AlgorithmTypeFunctions.c"
#include "PID.c"

PID Encoder_move[5];

#include "PID_Usage.c"
#include "PID_tasks.c"
#include "PID_Start.c"
#include "PID_LineFollower.c"
#include "PID_Gyro.c"
#include "PID_Encoder.c"
#include "PID_Functions.c"
#include "PID_Advanced.c"
#include "Tasks.c"

task main()
{
	PID_init(Encoder_move[0], 0.1, 0, 0, 0.0004, 20, -20, 0, 5);
	PID_init(Encoder_move[1], 0.2, 0, 0.0003, 0.0004, 40, -40, 0, 15);
	PID_init(Encoder_move[2], 0.25, 0, 0.0007, 0.0004, 50, -50, 0, 30);
	PID_init(Encoder_move[3], 0.75, 0.0000001, 0.0011, 0.0004, 75, -75, 0, 50);
	PID_init(Encoder_move[4], 1, 0.00002, 0.0016, 0.0004, 100, -100, 0, 70);

	Encoder_move[0].gearChangeValue = 10;
	Encoder_move[1].gearChangeValue = 30;
	Encoder_move[2].gearChangeValue = 75;
	Encoder_move[3].gearChangeValue = 150;

	for(int i = 0; i < 5; i++)
	{
		task_usage[i].use = none;
		task_prevUsage[i].use = none;
	}

	startTask(PID_LineFollower);
	startTask(PID_gyro);
	startTask(PID_Encoder);

	Encoder_moveMm_Advanced(1500);

	//Encoder_moveMm(Encoder_move[4], 1500);

	wait(3000);
}
