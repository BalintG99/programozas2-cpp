#pragma once
class Request
{
	static const unsigned MAX_LEVEL = 18;
private:
	unsigned start;
	unsigned destination;
public:
	Request(unsigned=0, unsigned=1);
	Request(const Request&);
	bool operator==(const Request&) const;
	bool operator!=(const Request&) const;
	bool isMovingUp() const;
	bool isInbetween(const Request&);
	unsigned getStart() const;
	unsigned getDestination() const;
	~Request();
};

