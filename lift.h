#pragma once
#include "fifo.h"
#include "Request.h"
#include <iostream>
#include <fstream>
#include <time.h>
class lift
{
private:
	bool isOn;
	bool isOpen;
	bool isup;
	unsigned position; 
	unsigned wpn; 
	unsigned* wayPoints;

public:
	lift();
	void openDoor(std::ofstream&);
	void closeDoor(std::ofstream&);
	void addWaypoint(const Request&);
	bool removeWaypoint();
	unsigned& Waypoint_front();
	void moveTo(unsigned, std::ofstream&);
	bool planRoute(fifo&);
	void work(fifo&);
	~lift();
};

