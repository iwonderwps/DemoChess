#pragma once

/****************************************************************************************
* Author:	Gilles Bellot
* Date:		03/07/2017 - Dortmund - Germany
*
* Desc:		A high-perfomance timer powered by the Windows perfomance counter
*
****************************************************************************************/

// INCLUDES /////////////////////////////////////////////////////////////////////////////

// CLASSES //////////////////////////////////////////////////////////////////////////////
class Timer
{
private:
	// times measured in counts
	// time at the start of the application
	long long int startTime;
	// total time the game was idle
	long long int totalIdleTime;
	// time at the moment the game was paused last
	long long int pausedTime;
	// stores the current time; i.e. time at the current frame
	long long int currentTime;
	// stores the time at the last inquiry before current; i.e. time at the previous frame
	long long int previousTime;
	// times measured in seconds
	// reciprocal of the frequency, computed once at the initialization of the class
	double secondsPerCount;
	// time between two frames, updated during the game loop
	double deltaTime;
	// state of the timer
	// true iff the timer is stopped
	bool isStopped;
public:
	Timer();
	~Timer();
public:
	// getters: return time measured in seconds
	// returns the total time the game has been running (minus paused time)
	double getTotalTime() const;
	// returns the time between two frames
	double getDeltaTime() const;
	// starts the timer, called each time the game is unpaused
	void start();
	// sets the counter to zero, called once before message loop
	void reset();
	// called every frame, lets the time tick
	void tick();
	// called when the game is paused
	void stop();
};
