#pragma once
#include "Request.h"

class fifo
{
private:
	unsigned elements;
	Request* pData;
public:
	fifo();
	void loadFile(const char[] = "lista_be.txt");
	bool isEmpty();
	bool isNew(const Request&);
	unsigned getElements();
	Request getPdata(unsigned);
	bool push(const Request&);
	void print(); 
	void takeOut(const Request&);
	Request& front();
	void pop();
	~fifo();
};

