#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
#include <cstring>
#include <cstdlib>
#include <stdio.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <fcntl.h> 
#include <pthread.h>

using namespace std;


class PageEntry
{
public:
	bool isValid;
	int index;
};

struct queueEntry
{
public:
	int index;
	struct queueEntry * next;
};

class TLBEntry
{
public:
	bool isOccupied;
	bool isModified;
	bool isReferenced;
	int frameNo;
	int usage;
};

class Queue
{
    int size;
    struct queueEntry * head;
public:
	Queue()
	{
		this->size = 10;
		head = NULL;
	}

	Queue(int size)
	{
		this->size = size;
		head = NULL;
	}

    void enqueue(int physIndex)
    {
    	//fprintf(stdout, "enqueue start\n");
    	if(head == NULL)
    	{
    		head = (struct queueEntry *) malloc(sizeof(struct queueEntry));
    		head->index = physIndex;
    		head->next = NULL;
    	}
    	else
    	{
    		struct queueEntry * newEntry = (struct queueEntry *) malloc(sizeof(struct queueEntry));
    		newEntry->index = physIndex;
    		newEntry->next = NULL;
    		struct queueEntry * temp = head;
    		while(temp->next != NULL)
    		{
    			temp = temp->next;
    		}
    		temp->next = newEntry;
    	}
    	//fprintf(stdout, "enqueue finish\n");
    }                     
	
	int dequeue()
	{
    	//fprintf(stdout, "dequeue start\n");
		if(head == NULL)
			return -1;
		int physIndex = head->index;
		struct queueEntry * temp = head;
		head = head->next;
		free(temp);
    	//fprintf(stdout, "dequeue finish\n");
		return physIndex;
	}

	~Queue()
	{
		while(dequeue() != -1)
		{

		}
	}
};

class Memory
{
private:

	static int ** physicalMemory;
	static PageEntry * pageTable;
	static TLBEntry * tlbTable;

	static int frameSize;
	static int physicalMemSize;
	static int virtualMemSize;
	static int pageTablePrintInterval;
	static int fd;
	static int pageReplacement;
	static int nruCounter;

	static int readCount[6];
	static int writeCount[6];
	static int pageReplacementCount[6];
	static int pageMissCount[6];
	static int diskReadCount[6];
	static int diskWriteCount[6];

	static char filename[50];
	
	static bool isAllocLocal;

	static Queue queue;

	static pthread_t bubbleSortThread;
	static pthread_t quickSortThread;
	static pthread_t mergeSortThread;
	static pthread_t indexSortThread;
	static pthread_t fillThread;
	static pthread_t checkThread;

	static pthread_mutex_t mutex; 
public:
	/*
	Memory(int frSize, int numPhys, int numVirt, const char * pageRep, bool allocationType, int interval, const char * file)
	{

	}
	*/

	void init(int frSize, int numPhys, int numVirt, const char * pageRep, bool allocationType, int interval, const char * file);

	//int getVirtualMemSize()	{ return virtualMemSize; }

	//int getPhysicalMemSize()	{ return physicalMemSize; }

	static void set(unsigned int index, int value, char * tName);

	static int get(unsigned int index, char * tName);

	static void swapValues(int index1, int index2, char * tName);

	static int replacePage(int frameNo, char * tName);

	static int findLRU();

	static int findNRU();

	static void resetNRU();

	static int findWSClock();

	static int findFIFO();

	static int findSC();

	static void * bubbleSortWorker(void *);

	static void * quickSortWorker(void *);

	static int partition (int low, int high, char * tName); 

	static void quickSort(int low, int high, char * tName);

	static void merge(int left, int mid, int right, char * tName); 

	static void mergeSort(int left, int right, char * tName);

	static void * mergeSortWorker(void *);

	static void * indexSortWorker(void *);

	static void * fillWorker(void *);

	static void * checkWorker(void *);

	static void debugPageTable();

	static void debugTLB();

	static void debugPhysicalMemory(int frameNo);
};



