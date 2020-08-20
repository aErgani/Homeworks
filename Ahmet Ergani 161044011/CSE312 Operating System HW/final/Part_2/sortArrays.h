#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
#include <cstdlib>
#include <stdio.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <fcntl.h> 
#include "memory.h"

#define KB_SIZE 1024
#define MB_SIZE 1048576
#define BOOL_SIZE 1
#define CHAR_SIZE 1
#define INT_SIZE 4

class SortArrays
{
private:
	int frameSize;
	int numPhysical;
	int numVirtual;
	int pageTablePrintInterval;
	char pageReplacement[8];
	char filename[50];
	bool isAllocLocal;

public:
	Memory * memory;
	SortArrays(int frSize, int numPhys, int numVirt, const char * pageRep, const char * allocationType, int interval, const char * file)
	{
		frameSize =  frSize;
		numPhysical = numPhys;
		numVirtual = numVirt;
		strcpy(pageReplacement, pageRep);
		if(strcmp("local", allocationType) == 0)
			isAllocLocal = true;
		else
			isAllocLocal = false;
		pageTablePrintInterval = interval;
		strcpy(filename, file);
		Memory memory;
		memory.init(frameSize, numPhysical, numVirtual, pageReplacement, isAllocLocal, pageTablePrintInterval, filename);
	}
};