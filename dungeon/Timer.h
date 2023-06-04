/***********************************************************************
 * File: Timer.h
 * Author: 劉耀恩
 * Create Date: 2023/04/29
 * Editor: 劉耀恩
 * Update Date: 2023/04/29
 * Description:
***********************************************************************/
#pragma once
#include <ctime>
class Timer
{
public:
	Timer(int);
	Timer(int, bool);
	bool tick();
	void start();
	void stop();
private:
	int interval;
	bool started = false;
	clock_t startTime;
	clock_t endTime;
}; 
// Intent: Constructor for Timer
// Pre: i is an integer representing the interval of the timer
// Post: A Timer object is created with the interval i
Timer::Timer(int i) : interval(i), startTime(clock()), endTime(clock())
{
}
// Intent: Constructor for Timer , with a bool to start at the beginning
// Pre: i is an integer representing the interval of the timer , if has any value of b the timer will start
// Post: A Timer object is created with the interval i , and started if b is defined
Timer::Timer(int i,bool) : interval(i), startTime(clock()), endTime(clock())
{
	started = true;
}
// Intent: Starts the timer , to make sure you know when the timer starts
// Pre: None
// Post: no return value, the timer is started
void Timer::start()
{
	startTime = clock();
	started = true;
}
// Intent: Stops the timer
// Pre: None
// Post: no return value, the timer is stopped
void Timer::stop()
{
	started = false;
}
// Intent: Checks if the timer has ticked , wont tick if the timer has not been started
// Pre: None
// Post: Returns true if the timer has ticked, false otherwise
bool Timer::tick()
{
	if (!started)
	{
		return false;
	}
	endTime = clock();
	if (endTime - startTime >= interval)
	{
		startTime = clock();
		return true;
	}
	return false;
}


