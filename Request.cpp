#include "Request.h"
#include <iostream>

using namespace std;


Request::Request(unsigned s, unsigned d)
{
	try {
		if (s > MAX_LEVEL || s < 0)
			throw 1;
		if (d > MAX_LEVEL || d < 0)
			throw 2;
		if (d == s)
			throw 3;
	}
	catch (int x)
	{
	if (x == 1)
		cout << "A kiindulasi szintnek 0 es " << MAX_LEVEL << "koze kell esnie! - ERROR " << x << endl;
	if (x==2)
		cout << "Az erkezesi szintnek 0 es " << MAX_LEVEL << "koze kell esnie! - ERROR " << x << endl;
	if (x == 3)
		cout << "A kiindulas es az erkezesi szintnek kulonbozonek kell lennie! - ERROR " << x << endl;
	}

	start = s;
	destination = d;

}

Request::Request(const Request & other): start (other.start), destination (other.destination)
{
}

unsigned Request::getStart() const
{
	return start;
}

unsigned Request::getDestination() const
{
	return destination;
}

bool Request::operator==(const Request& r) const {
	return (start == r.getStart() && destination == r.getDestination());
}

bool Request::operator!=(const Request& r) const {
	return (start != r.getStart() || destination != r.getDestination());
}


bool Request::isMovingUp() const
{
	return destination > start;
}

// a paraméterként kapott kérés teljesíthetõ-e azzal egyidõben, amire meghívtuk?
bool Request::isInbetween(const Request& r)
{
	if (isMovingUp() != r.isMovingUp())
		return false;
	else
	{
		if (this->isMovingUp())
		{
			return (this->start <= r.start && this->destination >= r.destination);
		}
		else
		{
			return (this->start >= r.start && this->destination <= r.destination);
		}
	}
}

Request::~Request()
{
}
