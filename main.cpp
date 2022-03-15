#include "fifo.h"
#include "lift.h"
#include "Request.h"
#include <iostream>
#include <fstream>

using namespace std;

int main() 
{
	lift l;
	fifo f;
	f.loadFile();
	l.work(f);
	return 0;
}