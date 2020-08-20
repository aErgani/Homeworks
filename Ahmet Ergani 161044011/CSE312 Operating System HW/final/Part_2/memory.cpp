#include "memory.h"

#define LRU 0
#define NRU 1
#define FIFO 2
#define WSCLOCK 3
#define SC 4

int ** Memory::physicalMemory;
PageEntry * Memory::pageTable;
TLBEntry * Memory::tlbTable;

int Memory::frameSize;
int Memory::physicalMemSize;
int Memory::virtualMemSize;
int Memory::pageTablePrintInterval;
int Memory::fd;
int Memory::pageReplacement;
int Memory::nruCounter;

int Memory::readCount[6];
int Memory::writeCount[6];
int Memory::pageReplacementCount[6];
int Memory::pageMissCount[6];
int Memory::diskReadCount[6];
int Memory::diskWriteCount[6];

char Memory::filename[50];

bool Memory::isAllocLocal;

Queue Memory::queue;

pthread_t Memory::bubbleSortThread;
pthread_t Memory::quickSortThread;
pthread_t Memory::mergeSortThread;
pthread_t Memory::indexSortThread;
pthread_t Memory::fillThread;
pthread_t Memory::checkThread;

pthread_mutex_t Memory::mutex; 

int pow2(int num);                 

/*
Memory(int frSize, int numPhys, int numVirt, const char * pageRep, bool allocationType, int interval, const char * file)
{
	srand(1000);
	if(numVirt < numPhys)
	{
		fprintf(stderr, "Virtual Memory Size must be bigger than physical Memory Size\n");
	}
    physicalMemSize = numPhys;
    virtualMemSize = numVirt;
    frameSize = frSize;

    strcpy(pageReplacement, pageRep);
	isAllocLocal = allocationType;
	pageTablePrintInterval = interval;
	strcpy(filename, file);

}
*/

void Memory::init(int frSize, int numPhys, int numVirt, const char * pageRep, bool allocationType, int interval, const char * file)
{
	srand(1000);
	if(numVirt < numPhys)
	{
		fprintf(stderr, "Virtual Memory Size must be bigger than physical Memory Size\n");
	}
    Memory::physicalMemSize = pow2(numPhys);
    Memory::virtualMemSize = pow2(numVirt);
    Memory::frameSize = pow2(frSize);

	fprintf(stdout, "Virtual Memory Size: %d\nPhysical Memory Size: %d\nFrame Size: %d\n", Memory::virtualMemSize, Memory::physicalMemSize, Memory::frameSize);

	isAllocLocal = allocationType;
	pageTablePrintInterval = interval;
	strcpy(filename, file);

	fprintf(stdout, "Replacement Algorithm: %s\nInterval: %d\nFile: %s\n", pageRep, pageTablePrintInterval, filename);

	if(strcmp(pageRep, "LRU") == 0)
	{
		pageReplacement = LRU;
	}
	if(strcmp(pageRep, "NRU") == 0)
	{
		pageReplacement = NRU;
		nruCounter = 0;
	}
	if(strcmp(pageRep, "WSClock") == 0)
	{
		pageReplacement = WSCLOCK;
	}
	if(strcmp(pageRep, "FIFO") == 0)
	{
		pageReplacement = FIFO;
	}
	if(strcmp(pageRep, "SC") == 0)
	{
		pageReplacement = SC;
	}

	if(pageReplacement == SC || pageReplacement == FIFO || pageReplacement == WSCLOCK)
	{
		queue = Queue(physicalMemSize);
	}

	//allocate physical memory
    physicalMemory = new int *[physicalMemSize];
    tlbTable = new TLBEntry [physicalMemSize];
	for(int i = 0; i < physicalMemSize; i++)
	{
	    physicalMemory[i] = new int[frameSize];
	    tlbTable[i].isOccupied = false;
	    tlbTable[i].isReferenced = false;
	    tlbTable[i].usage = 0;
	}

	pageTable = new PageEntry [virtualMemSize];

	for(int i = 0; i < virtualMemSize; i++)
	{
		pageTable[i].isValid = false;
	}

	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	int val;
	int zero = 0;
	lseek(fd, 0, SEEK_SET);
	for(int i = 0; i < virtualMemSize * frameSize; i++)
	{
		val = write(fd, &zero, sizeof(zero));
		if(val < 0)
		{
			fprintf(stderr, "Write error\n");
			exit(EXIT_FAILURE);
		}
	}

	pthread_mutex_init(&mutex, NULL);

	/*
	int data = 22;
	int data2 = 25;
	lseek(fd, 0, SEEK_SET);
	val = write(fd, &data, sizeof(int));
	val = write(fd, &data2, sizeof(int));
	*/
    pthread_create(&fillThread, NULL, fillWorker, NULL);
    pthread_join(fillThread, NULL);
    /*
    for (int i = 0; i < physicalMemSize; i++)
    {
    	lseek(fd, tlbTable[i].frameNo * frameSize * sizeof(int), SEEK_SET);
		for(int j = 0 ; j < frameSize; j++)
		{
			val = write(fd, &physicalMemory[i][j], sizeof(int));
		}
    }
    */

    pthread_create(&bubbleSortThread, NULL, bubbleSortWorker, NULL);
    pthread_create(&quickSortThread, NULL, quickSortWorker, NULL);
    pthread_create(&mergeSortThread, NULL, mergeSortWorker, NULL);
    pthread_create(&indexSortThread, NULL, indexSortWorker, NULL);
   	pthread_join(mergeSortThread, NULL);
    pthread_join(bubbleSortThread, NULL);
    pthread_join(quickSortThread, NULL);
    pthread_join(indexSortThread, NULL);
	
    pthread_create(&checkThread, NULL, checkWorker, NULL);
    pthread_join(checkThread, NULL);
	close(fd);
    
}

//int getVirtualMemSize()		{ return virtualMemSize; }

//int getPhysicalMemSize()	{ return physicalMemSize; }

void Memory::set(unsigned int index, int value, char * tName)
{
	pthread_mutex_lock(&mutex);
    int frameNo = index / frameSize;
    int dataIndex = index % frameSize;
    int physIndex;

    if(strcmp(tName, "fill") == 0)
    {
    	writeCount[0]++;
    }
    else if(strcmp(tName, "bubble") == 0)
    {
    	writeCount[1]++;
    }
    else if(strcmp(tName, "quick") == 0)
    {
    	writeCount[2]++;
    }
    else if(strcmp(tName, "merge") == 0)
    {
    	writeCount[3]++;
    }
    else if(strcmp(tName, "index") == 0)
    {
    	writeCount[4]++;
    }
    else if(strcmp(tName, "check") == 0)
    {
    	writeCount[5]++;
    }
    
    if(pageTable[frameNo].isValid)
    {
    	physicalMemory[pageTable[frameNo].index][dataIndex] = value;

    	tlbTable[pageTable[frameNo].index].isModified = true;
		tlbTable[pageTable[frameNo].index].isReferenced = true;
		tlbTable[pageTable[frameNo].index].usage = 0;
    }
    else
    {
    	physIndex = replacePage(frameNo, tName);

    	physicalMemory[physIndex][dataIndex] = value;

    	tlbTable[physIndex].isModified = true;
		tlbTable[physIndex].isOccupied = true;
		tlbTable[physIndex].frameNo = frameNo;
		tlbTable[physIndex].usage = 0;

		pageTable[frameNo].isValid = true;
		pageTable[frameNo].index = physIndex;
		tlbTable[physIndex].isReferenced = true;
		
    }
    
    if(pageReplacement == NRU)
    {
    	nruCounter++;
    	if(nruCounter == physicalMemSize * frameSize / 2)
    	{
    		resetNRU();
    	}
    	
    }	

    for (int i = 0; i < physicalMemSize; ++i)
    {
    	tlbTable[i].usage++;
    }
	pthread_mutex_unlock(&mutex);
}

int Memory::get(unsigned int index, char * tName)
{
    pthread_mutex_lock(&mutex);
    int frameNo = index / frameSize;
    int dataIndex = index % frameSize;
    int physIndex, value;

    if(strcmp(tName, "fill") == 0)
    {
    	readCount[0]++;
    }
    else if(strcmp(tName, "bubble") == 0)
    {
    	readCount[1]++;
    }
    else if(strcmp(tName, "quick") == 0)
    {
    	readCount[2]++;
    }
    else if(strcmp(tName, "merge") == 0)
    {
    	readCount[3]++;
    }
    else if(strcmp(tName, "index") == 0)
    {
    	readCount[4]++;
    }
    else if(strcmp(tName, "check") == 0)
    {
    	readCount[5]++;
    }
    
    if(pageTable[frameNo].isValid)
    {
    	value = physicalMemory[pageTable[frameNo].index][dataIndex];
		tlbTable[pageTable[frameNo].index].usage = 0;
		tlbTable[pageTable[frameNo].index].isReferenced = true;
		
    }
    else
    {
    	physIndex = replacePage(frameNo, tName);
    	value = physicalMemory[physIndex][dataIndex];
		tlbTable[physIndex].isOccupied = true;
		tlbTable[physIndex].frameNo = frameNo;
		tlbTable[physIndex].usage = 0;
		pageTable[frameNo].isValid = true;
		pageTable[frameNo].index = physIndex;
    	tlbTable[physIndex].isReferenced = true;
    }
    
    if(pageReplacement == NRU)
    {
    	nruCounter++;
    	if(nruCounter == physicalMemSize * frameSize / 2)
    	{	
    		resetNRU();
    	}
    }

    for (int i = 0; i < physicalMemSize; ++i)
    {
    	tlbTable[i].usage++;
    }
    pthread_mutex_unlock(&mutex);
    return value;
}

int Memory::replacePage(int frameNo, char * tName)
{
	int val, data, physIndex;
	switch(pageReplacement)
	{
		case LRU:
			physIndex = findLRU();
			break;

		case NRU:
			physIndex = findNRU();
			break;

		case WSCLOCK:
			physIndex = findWSClock();
			break;

		case FIFO:
			physIndex = findFIFO();
			queue.enqueue(physIndex);
			break;

		case SC:
			physIndex = findSC();
			break;

		default:
			break;
	}
	if(tlbTable[physIndex].isOccupied && tlbTable[physIndex].isModified)
	{
		lseek(fd, tlbTable[physIndex].frameNo * frameSize * sizeof(int), SEEK_SET);

		for(int i = 0 ; i < frameSize; i++)
		{
			val = write(fd, &physicalMemory[physIndex][i], sizeof(int));
		}
		if(strcmp(tName, "fill") == 0)
	    {
	    	diskWriteCount[0]++;
	    }
	    else if(strcmp(tName, "bubble") == 0)
	    {
	    	diskWriteCount[1]++;
	    }
	    else if(strcmp(tName, "quick") == 0)
	    {
	    	diskWriteCount[2]++;
	    }
	    else if(strcmp(tName, "merge") == 0)
	    {
	    	diskWriteCount[3]++;
	    }
	    else if(strcmp(tName, "index") == 0)
	    {
	    	diskWriteCount[4]++;
	    }
	    else if(strcmp(tName, "check") == 0)
	    {
	    	diskWriteCount[5]++;
	    }
	}
	pageTable[tlbTable[physIndex].frameNo].isValid = false;
	if(strcmp(tName, "fill") == 0)
    {
    	diskReadCount[0]++;
    	pageReplacementCount[0]++;
    }
    else if(strcmp(tName, "bubble") == 0)
    {
    	diskReadCount[1]++;
    	pageReplacementCount[1]++;
    }
    else if(strcmp(tName, "quick") == 0)
    {
    	diskReadCount[2]++;
    	pageReplacementCount[2]++;
    }
    else if(strcmp(tName, "merge") == 0)
    {
    	diskReadCount[3]++;
    	pageReplacementCount[3]++;
    }
    else if(strcmp(tName, "index") == 0)
    {
    	diskReadCount[4]++;
    	pageReplacementCount[4]++;
    }
    else if(strcmp(tName, "check") == 0)
    {
    	diskReadCount[5]++;
    	pageReplacementCount[5]++;
    }
	lseek(fd, frameNo * frameSize * sizeof(int), SEEK_SET);
	for(int i = 0 ; i < frameSize; i++)
	{
		val = read(fd, &data, sizeof(data));
		physicalMemory[physIndex][i] = data;
	}
	return physIndex;
}

int Memory::findLRU()
{
	int lruIndex = 0;
	int max = 0;
	for(int i = 0; i < physicalMemSize; i++)
	{
		if (!tlbTable[i].isOccupied)
		{
			return i;
		}
		else if(tlbTable[i].usage > max)
		{
			lruIndex = i;
			max = tlbTable[i].usage;
		}
	}
	return lruIndex;
}

int Memory::findNRU()
{
	for (int i = 0; i < physicalMemSize; i++)
	{
		if (!tlbTable[i].isReferenced)
		{
			return i;
		}
	}
	return 0;
}

void Memory::resetNRU()
{
	//debugTLB();
	for (int i = 0; i < physicalMemSize; i++)
	{
		tlbTable[i].isReferenced = false;
	}
	nruCounter = 0;
}

int Memory::findWSClock()
{
	
}

int Memory::findFIFO()
{
	for(int i = 0; i < physicalMemSize; i++)
	{
		if (!tlbTable[i].isOccupied)
		{
			return i;
		}
	}
	return queue.dequeue();
}	

int Memory::findSC()
{

}


void * Memory::bubbleSortWorker(void *)
{
	char tName[7] = "bubble";
	readCount[1] = 0;
	writeCount[1] = 0;
	pageReplacementCount[1] = 0;
	pageMissCount[1] = 0;
	diskReadCount[1] = 0;
	diskWriteCount[1] = 0;
	int N = (virtualMemSize * frameSize) / 4;
    for (int i = 0; i < N; i++) 
    { 
        for (int j = 0; j < N - i - 1; j++) 
        {
            if (get(j, tName) > get(j + 1, tName)) 
            {  
                swapValues(j, j + 1, tName);
            }
        }
    }

	return NULL;
}

int Memory::partition (int low, int high, char * tName) 
{ 
    int i = low - 1;
    int pivot = get(high, tName);
  
    for (int j = low; j <= high- 1; j++) 
    { 
        if (get(j, tName) < pivot) 
        { 
            i++;
            swapValues(i, j, tName); 
        } 
    } 
    swapValues(i + 1, high, tName); 
    return (i + 1); 
} 
  
void Memory::quickSort(int low, int high, char * tName) 
{ 
    if (low < high) 
    {
        int pi = partition(low, high, tName); 
        quickSort(low, pi - 1, tName); 
        quickSort(pi + 1, high, tName); 
    } 
} 

void Memory::swapValues(int index1, int index2, char * tName)
{
	//if(tName[0] == 'i')
		
	//fprintf(stdout, "%s swap index1 : %d index2 : %d\n", tName, index1, index2);
	int temp = get(index1, tName);
    set(index1, get(index2, tName), tName);
    set(index2, temp, tName);
}

void * Memory::quickSortWorker(void *)
{
	readCount[2] = 0;
	writeCount[2] = 0;
	pageReplacementCount[2] = 0;
	pageMissCount[2] = 0;
	diskReadCount[2] = 0;
	diskWriteCount[2] = 0;
	char tName[6] = "quick"; 
	int N = (virtualMemSize * frameSize) / 4;
	quickSort(N , N * 2 - 1, tName);

	return NULL;
}


void Memory::merge(int left, int mid, int right, char * tName) 
{ 
    int N1 = mid - left + 1; 
    int N2 = right - mid; 
  
    int first[N1], second[N2]; 
  
    for (int i = 0; i < N1; i++) 
	{
        first[i] = get(left + i, tName); 
	}
    for (int j = 0; j < N2; j++) 
    {
        second[j] = get(mid + 1 + j, tName); 
    }
  
    int i = 0, j = 0, k = left; 

    while (i < N1 && j < N2) 
    { 
        if (first[i] <= second[j]) 
        { 
        	set(k, first[i], tName);
            i++; 
        } 
        else 
        { 
        	set(k, second[j], tName);
            j++; 
        } 
        k++; 
    } 

    while (i < N1) 
    { 
    	set(k, first[i], tName);
        i++; 
        k++; 
    } 
    while (j < N2) 
    { 
    	set(k, second[j], tName);
        j++; 
        k++; 
    } 
} 
 
void Memory::mergeSort(int left, int right, char * tName) 
{
     if (left < right) 
     { 
        int mid = left + (right - left) / 2; 

        mergeSort(left, mid, tName); 
        mergeSort(mid + 1, right, tName); 
  
        merge(left, mid, right, tName); 
    } 
} 

void * Memory::mergeSortWorker(void *)
{
	readCount[3] = 0;
	writeCount[3] = 0;
	pageReplacementCount[3] = 0;
	pageMissCount[3] = 0;
	diskReadCount[3] = 0;
	diskWriteCount[3] = 0;
	char tName[6] = "merge";
	int N = (virtualMemSize * frameSize) / 4;
	mergeSort(N * 2 , N * 3 - 1, tName);

	return NULL;
}

void * Memory::indexSortWorker(void *)
{
	readCount[4] = 0;
	writeCount[4] = 0;
	pageReplacementCount[4] = 0;
	pageMissCount[4] = 0;
	diskReadCount[4] = 0;
	diskWriteCount[4] = 0;
	char tName[6] = "index";
	int N = (virtualMemSize * frameSize) / 4;
	int indexes[N];
	int values[N];
	for (int i = 0; i < N; ++i)
	{
		indexes[i] = i + N * 3;
	}

	for (int i = 0; i < N; i++) 
    { 
        for (int j = i + 1; j < N; j++) 
        { 
            if (get(indexes[i], tName) > get(indexes[j], tName)) 
            { 
                int temp = indexes[i]; 
                indexes[i] = indexes[j]; 
                indexes[j] = temp; 
            } 
        } 
    }

    for (int i = 0; i < N; ++i)
	{
		values[i] = get(indexes[i], tName);
	}
	for (int i = 0; i < N; ++i)
	{
		set(i + N * 3, values[i], tName);
	}

	return NULL;
}

void * Memory::fillWorker(void *)
{
	readCount[0] = 0;
	writeCount[0] = 0;
	pageReplacementCount[0] = 0;
	pageMissCount[0] = 0;
	diskReadCount[0] = 0;
	diskWriteCount[0] = 0;
	char tName[5] = "fill";
	for(int i = 0; i < (frameSize * virtualMemSize); i++)
	{
		int random = rand();
		random = random % 100;
		set(i, random, tName);
	}
	return NULL;
}

void * Memory::checkWorker(void *)
{
	readCount[5] = 0;
	writeCount[5] = 0;
	pageReplacementCount[5] = 0;
	pageMissCount[5] = 0;
	diskReadCount[5] = 0;
	diskWriteCount[5] = 0;
	char tName[6] = "check";
	int N = (frameSize * virtualMemSize) / 4;
	for(int i = 0; i < N - 1; i++)
	{
		if(get(i, tName) > get(i + 1, tName))
		{
			fprintf(stdout, "Array is not sorted\n");
		}
	}
	for(int i = N; i < N * 2 - 1; i++)
	{
		if(get(i, tName) > get(i + 1, tName))
		{
			fprintf(stdout, "Array is not sorted\n");
		}
	}
	for(int i = N * 2; i < N * 3- 1; i++)
	{
		if(get(i, tName) > get(i + 1, tName))
		{
			fprintf(stdout, "Array is not sorted\n");
		}
	}
	for(int i = N * 3; i < N * 4 - 1; i++)
	{
		if(get(i, tName) > get(i + 1, tName))
		{
			fprintf(stdout, "Array quarters are not sorted\n");
			exit(EXIT_FAILURE);
		}
	}
	fprintf(stdout, "\nArray quarters are sorted\n\n");
	fprintf(stdout, "FILL : read: %d\t\twrite: %d\tpage miss: %d\tpage replacement : %d\tdisk read : %d\tdisk write : %d\n",
		readCount[0], writeCount[0], pageReplacementCount[0], (pageReplacementCount[0] - physicalMemSize), diskReadCount[0], diskWriteCount[0]);
	fprintf(stdout, "BUBBLE : read: %d\twrite: %d\tpage miss: %d\tpage replacement : %d\tdisk read : %d\tdisk write : %d\n",
		readCount[1], writeCount[1], pageReplacementCount[1], (pageReplacementCount[1] - physicalMemSize), diskReadCount[1], diskWriteCount[1]);
	fprintf(stdout, "QUICK : read: %d\twrite: %d\tpage miss: %d\tpage replacement : %d\tdisk read : %d\tdisk write : %d\n",
		readCount[2], writeCount[2], pageReplacementCount[2], (pageReplacementCount[2] - physicalMemSize), diskReadCount[2], diskWriteCount[2]);
	fprintf(stdout, "MERGE : read: %d\twrite: %d\tpage miss: %d\tpage replacement : %d\tdisk read : %d\tdisk write : %d\n",
		readCount[3], writeCount[3], pageReplacementCount[3], (pageReplacementCount[3] - physicalMemSize), diskReadCount[3], diskWriteCount[3]);
	fprintf(stdout, "INDEX : read: %d\twrite: %d\tpage miss: %d\tpage replacement : %d\tdisk read : %d\tdisk write : %d\n",
		readCount[4], writeCount[4], pageReplacementCount[4], (pageReplacementCount[4] - physicalMemSize), diskReadCount[4], diskWriteCount[4]);
	fprintf(stdout, "CHECK : read: %d\twrite: %d\tpage miss: %d\tpage replacement : %d\tdisk read : %d\tdisk write : %d\n",
		readCount[5], writeCount[5], pageReplacementCount[5], (pageReplacementCount[5] - physicalMemSize), diskReadCount[5], diskWriteCount[5]);

	return NULL;
}

int pow2(int num)
{
	if(num == 0)
		return 1;
	int value = 1;
	for(int i = 0; i < num; i++)
	{
		value *= 2;
	}
	return value;
}

void Memory::debugPageTable()
{
	for(int i = 0; i < virtualMemSize; i++)
	{
		int valid = pageTable[i].isValid ? 1 : 0;
		fprintf(stdout, "pageTable[%d] -> isValid : %d index : %d\n", i, valid, pageTable[i].index);
	}
}

void Memory::debugTLB()
{
	for(int i = 0; i < physicalMemSize; i++)
	{
		int occupation = tlbTable[i].isOccupied ? 1 : 0;
		int modification = tlbTable[i].isModified ? 1 : 0;
		int referenced = tlbTable[i].isReferenced ? 1 : 0;
		fprintf(stdout, "tlbTable[%d] -> isOccupied : %d isModified : %d isReferenced : %d frameNo : %d usage : %d\n", i, occupation, modification, referenced, tlbTable[i].frameNo, tlbTable[i].usage);
	}
}

void Memory::debugPhysicalMemory(int frameNo)
{
	if(frameNo == physicalMemSize || frameNo < 0)
		return;
	fprintf(stdout, "physicalMemory[%d]", frameNo);
	for (int i = 0; i < frameSize; i++)
	{
		fprintf(stdout, " %d", physicalMemory[frameNo][i]);
	}
	fprintf(stdout, "\n");
}

