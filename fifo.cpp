#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "fifo.h"
#include "request.h"

using namespace std;

fifo::fifo() : elements(0), pData (nullptr)
{
}

// hibakezelés!
void fifo::loadFile(const char fname[]) 
{
	cout << fname << " megnyitasa a lista feltoltesehez..." << endl;
	ifstream file(fname);
	try {
		if (!file.is_open())
			throw 5;
	}
	catch (int x)
	{
		cout << fname << " - file megnyitasa sikertelen - ERROR: " << x << endl;
	}
	unsigned s, d;
	while (!file.eof() && file.is_open()) 
	{
		try {
			if (!(file >> s >> d))
			{
				throw 6;
			}
		}
		catch (int x)
		{
			file.close();
			cout << fname << " formatuma nem megfelelo es/vagy a benne szereplo szamertekek nem nemnegativ egeszek! - ERROR: " << x << endl;
			break;
		}
		Request r = Request(s, d);
		push(r);
	}
	file.close();
}

bool fifo::isEmpty()
{
	if (elements)
		return 0;
	else
		return 1;
}

bool fifo::isNew(const Request& r) 
{
	Request* ptrTemp = pData;
	for (unsigned i = 0; i < this->elements; i++)
	{
		if (ptrTemp[i] == r)
			return false;
	}
	return true;
}

Request& fifo::front() {
	cout << "Keres teljesitese... (start: " << pData->getStart() << ", cel: " << pData->getDestination() << ")" << endl;
	return pData[0];
}

void fifo::pop() 
{
	try 
	{
		if (this->isEmpty())
			throw 4.1;
	} 
	catch (double x) 
	{
		cout << "A lista ures! - ERROR: " << x << endl;
	}
	Request *ptrTemp;
	ptrTemp = new Request[elements-1];
	for (unsigned i = 0; i < elements-1; i++)
	{
		ptrTemp[i] = pData[i+1];
	}
	delete[] pData;
	pData = ptrTemp;
	elements--;

	/*cout << "Keres teljesitve (start: " << pData->getStart() << ", cel: " << pData->getDestination() << ") , elem torlese a listabol..." << endl;
	Request *ptrTemp;
	ptrTemp = pData;
	pData++;
	delete ptrTemp;
	elements--;
	return r;*/
}

unsigned fifo::getElements()
{
	return elements;
}

Request fifo::getPdata(unsigned n)
{
	return pData[n];
}


bool fifo::push(const Request& newReq) 
{
	if (isNew(newReq))
	{
	Request *ptrTemp;
	ptrTemp = new Request[elements + 1];
	try {
		if (!ptrTemp)
			throw 7;
	}
	catch (int x)
	{
		cout << "Sikertelen helyfoglalas - ERROR: " << x << endl;
	}
	unsigned i;
	for (i = 0; i < elements; i++) {
		ptrTemp[i] = pData[i];
	}
	ptrTemp[i] = newReq;
	delete[] pData;
	pData = ptrTemp;
	elements++;
	cout << "Uj keres: start:" << newReq.getStart() << ", cel: " << newReq.getDestination() << endl;
	return 1;
}
	else
	{
		return 0;
	}
}

void fifo::print()
{
	ofstream log("lista_ki.txt");
	Request* ptrTemp=pData;
	try {
		if (this->isEmpty())
			throw 4.2;
	}
	catch (double x) {
		cout << "A lista ures! - ERROR: " << x << endl;
	}
	
	for (unsigned i = 0; i < elements; i++) {
		cout << i + 1 << ". elem: start: " << this->pData[i].getStart() << "  cel: " << this->pData[i].getDestination() << "\n" << endl;
		log << this->pData[i].getStart() << ' ' << this->pData[i].getDestination() << endl;
	}
}

void fifo::takeOut(const Request& r)
{
	try {
		if (this->isEmpty())
			throw 4.3;
	}
	catch (double x) {
		cout << "A lista ures! - ERROR: " << x << endl;
	}

	Request* ptrTemp = new Request[elements - 1];
	unsigned i;
	
	for (i=0; pData[i] != r; i++)
	{
		ptrTemp[i] = pData[i];
	}
	for (; i < elements - 1; i++)
	{
		ptrTemp[i] = pData[i + 1];
	}
	elements--;
	delete[] pData;
	pData = ptrTemp;
}


fifo::~fifo()
{
	delete[] pData;
}
