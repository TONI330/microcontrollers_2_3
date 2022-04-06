#pragma once

#define DRIVE_CLOCKWISE_SLOWEST_MS 1460
#define DRIVE_CLOCKWISE_FASTEST_MS 1300

#define DRIVE_COUNTERCLOCKWISE_SLOWEST_MS 1540
#define DRIVE_COUNTERCLOCKWISE_FASTEST_MS 1700

#define DRIVE_FULL_STOP_MS 1500

#define DRIVE_STEP_SIZE (DRIVE_CLOCKWISE_SLOWEST_MS - DRIVE_CLOCKWISE_FASTEST_MS) / 100.0

/*
	This method initializes the servos and the I/O pins they are
	connected to. The servos are initialized to stop turning.
	
	The servos are connected to pin D13 & D12 which are set to output in
	this method.
*/
void init_servos(void);

/*
	This method is used to set the speed of the servos.
	
	@param percentage_speed is the speed both servos will turn synchronously. 
	0-49 is backwards, 50 is stop, 51-100 is forwards.
	
	@param percentage_turn determines whether the servos should turn and in which direction.
	0-49 is turn left, 50 is don't turn, 51-100 is turn right.
*/
void control_drive(short percentage_speed, short percentage_turn);
