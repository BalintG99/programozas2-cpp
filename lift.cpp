#include "lift.h"
#include "fifo.h"
#include "Request.h"

using namespace std;


lift::lift() : isOn(0), isOpen(0), position(0), wpn(0), wayPoints(nullptr)
{
}


//hozzáadás, rendezés

void lift::addWaypoint(const Request& r)
{
	bool a= true;
	bool b = true;
	for (unsigned i = 0; i < wpn; i++)
	{
		if (r.getStart() == wayPoints[i])
			a = false;
		if (r.getDestination() == wayPoints[i])
			b = false;
	}
	isup = r.isMovingUp();
	if (a || b) {
		unsigned wpn_ideig = wpn + ((unsigned)a + (unsigned)b);
		unsigned* ptrTemp = new unsigned[wpn_ideig];
		unsigned c = 0;
		if (isup) {
			while (c < wpn && wayPoints[c] < r.getStart()) {
				ptrTemp[c] = wayPoints[c];
				c++;
			}
			if (a) {
				ptrTemp[c] = r.getStart();
			}
			while (c < wpn && wayPoints[c] < r.getDestination()) {
				ptrTemp[c + (unsigned)a] = wayPoints[c];
				c++;
			}
			if (b) {
				ptrTemp[c + (unsigned)a] = r.getDestination();
			}
			while (c < wpn) {
				ptrTemp[c + (unsigned)a + (unsigned)b] = wayPoints[c];
				c++;
			}
		}
		else{
			while (c < wpn && wayPoints[c] > r.getStart()) {
				ptrTemp[c] = wayPoints[c];
				c++;
			}
			if (a) {
				ptrTemp[c] = r.getStart();
			}
			while (c < wpn && wayPoints[c] > r.getDestination()) {
				ptrTemp[c + (unsigned)a] = wayPoints[c];
				c++;
			}
			if (b) {
				ptrTemp[c + (unsigned)a] = r.getDestination();
			}
			while (c < wpn) {
				ptrTemp[c + (unsigned)a + (unsigned)b] = wayPoints[c];
				c++;
			}
		}
		delete[] wayPoints;
		wayPoints = ptrTemp;
		wpn = wpn_ideig;
	}
}

unsigned& lift::Waypoint_front()
{
	return wayPoints[0];
}

bool lift::removeWaypoint() {
	if (wpn == 0) return false;
	unsigned* tmp = new unsigned[wpn - 1];
	for (unsigned i = 1; i < wpn; i++) {
		tmp[i-1] = wayPoints[i];
	}
	wpn = wpn - 1;
	delete[] wayPoints;
	wayPoints = tmp;
	return true;
}

void lift::closeDoor(ofstream& file)
{
	if (isOpen )
	{
		cout << "A liftajto becsukodik a " << position << ". emeleten" << endl;
		file << "A liftajto becsukodik a " << position << ". emeleten" << endl;
		isOpen = false;
	}
}

void lift::openDoor(ofstream& file)
{
	if (!isOpen)
	{
		cout << "A liftajto kinyilik a " << position <<". emeleten \n" << endl;
		file << "A liftajto kinyilik a " << position <<". emeleten \n" << endl;
		isOpen = true;
	}
}


//feltölti a 'wayPoints' tömböt
bool lift::planRoute(fifo& f)
{
	if (f.getElements() == 0)
		return false;
	Request r = f.front();
	addWaypoint(r);
	for (unsigned i = 1; i < f.getElements();)
	{
		if (r.isInbetween(f.getPdata(i)))
		{
			addWaypoint(f.getPdata(i));
			f.takeOut(f.getPdata(i));
		}
		else i++;
	}
	f.pop();
	return true;
	}


void lift::moveTo(unsigned d, ofstream& file)
{
	closeDoor(file);
	cout << "A lift elindul, uticel: " << d << endl;
	file << "A lift elindul, uticel: " << d << endl;
	position = d;
	openDoor(file);
}



void lift::work(fifo& f)
{
	try {
		if (f.getElements() == 0)
			throw 4.4;
	}
	catch (double x)
	{
		cout << "A lista ures! - ERROR: " << x << endl;
		return;
	}
	ofstream file("lift_log.txt");
	while (planRoute(f))
	{
		while (wpn)
		{
			moveTo(Waypoint_front(),file);
			removeWaypoint();
		}

	}
	file.close();
}

lift::~lift()
{
	delete[] wayPoints;
}
