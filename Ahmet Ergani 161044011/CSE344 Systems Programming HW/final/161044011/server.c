#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h> 
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/file.h>
#include <signal.h>
#include <wait.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <syslog.h>

#define LINE_SIZE 312
#define CACHE_SIZE 3131

struct edge
{
    int src;
    int dest;
}edge;

struct Graph {
  struct Node** adjLists;
  int* visited;
};

struct Node {
  int value;
  struct Node * next;
};

struct Queue {
  int * items;
  int front;
  int rear;
};

struct Path {
  int node;
  struct Path * next;
};

struct CacheEntry {
  int src;
  int dest;
  struct Path * path;
};

void flushLine(char * line);
struct Queue* createQueue();
void enqueue(struct Queue* q, int);
int dequeue(struct Queue* q);
int isEmpty(struct Queue* q);
struct Path * bfs(struct Graph* graph, int srcNode, int destNode); 
struct Node* createNode(int v);
void initGraph();
void initSocket(int port);
void initCache();
void addEdge(struct Graph* graph, int srcNode, int target);
void initThreads();
void expandThreadPool();
void * requestHandler(void* workerNo);
void assignTask(int src, int dest, int server_socket); 
void freeResources();
void * observer();
int calculateCacheHash(int src, int dest);
struct CacheEntry * getPathFromCache(int src, int dest);
void insertIntoCache(struct CacheEntry * entry);
void clearCache();


char * inputPath;
char * logPath;
int port;
int currentThreadCount;
int currentActiveThreadCount = 0;
int maxThreadCount;
int input_fd;
int log_fd;
int server_fd;


struct CacheEntry * cache_DB[CACHE_SIZE];

struct Graph * graph;

pthread_t observer_tid;

pthread_t * workers;
int * sockets;
int * srcNodes;
int * destNodes;
int * workerStatus;
pthread_mutex_t * locks; 

pthread_mutex_t observer_mutex;
pthread_mutex_t cache_mutex;

//struct edge * edges;
//int * nodes;

int NODE_COUNT;
int EDGE_COUNT;

int isServerShutdown = 0;

void signal_handler(int signum)     //Handles SIGINT signal
{
    char buffer[256];
    if(signum == SIGINT)
    {
        int i;
        isServerShutdown = 1;
        sprintf(buffer, "\nTermination signal received, waiting for ongoing threads to complete.\n");
        write(log_fd, buffer, strlen(buffer));
        memset(buffer, '\0', 256);
        for(i = 0; i < currentThreadCount; i++)
        {
            pthread_mutex_unlock(&locks[i]);
            pthread_join(workers[i], NULL);
        }
        pthread_mutex_unlock(&observer_mutex);
        pthread_join(observer_tid, NULL);
        sprintf(buffer, "All threads have terminated, server shutting down.\n");
        write(log_fd, buffer, strlen(buffer));
        memset(buffer, '\0', 256);
        freeResources();
        close(log_fd);
        exit(EXIT_SUCCESS);
    }
}

int main(int argc, char *argv[])
{
    if(argc < 3)
    {
        printf("Invalid argument count.\nNeeded 5 labeled argument. -i for inputPath -p for Port number -o logPath for -s for initial thread count -x for max thread count.\nTerminating...\n");
        exit(-1); 
    }

    int opt;
    char buffer[256];
    while((opt = getopt(argc,argv,"i:p:o:s:x:")) != -1)
    {  
        switch(opt)  
        {   
            case 'i':  
                inputPath = optarg;
                break;  
            case 'p':  
                port = atoi(optarg);
                break; 
            case 'o':  
                logPath = optarg;
                break; 
            case 's':  
                currentThreadCount = atoi(optarg);
                break; 
            case 'x':  
                maxThreadCount = atoi(optarg);
                break; 
            default:  
                fprintf(stderr,"unknown option: '%c' Needed 5 labeled argument. -i for inputPath -p for Port number -o logPath for -s for initial thread count -x for max thread count.\nTerminating...\n", opt);
                exit(-1); 
        }  
    }
    signal(SIGINT, signal_handler);
    log_fd = open(logPath, O_RDWR | O_CREAT | O_TRUNC);
    sprintf(buffer, "Path To Input File: %s\n", inputPath);  
    write(log_fd, buffer, strlen(buffer));
    memset(buffer, '\0', 256);
    sprintf(buffer, "Port: %d\n", port);  
    write(log_fd, buffer, strlen(buffer));
    memset(buffer, '\0', 256);
    sprintf(buffer, "Path To Log File: %s\n", logPath);  
    write(log_fd, buffer, strlen(buffer));
    memset(buffer, '\0', 256);
    sprintf(buffer, "Initial Thread Count: %d\n", currentThreadCount);
    write(log_fd, buffer, strlen(buffer));
    memset(buffer, '\0', 256);
    sprintf(buffer, "Max Thread Count: %d\n", maxThreadCount);  
    write(log_fd, buffer, strlen(buffer));
    memset(buffer, '\0', 256);  
    initGraph();
    initThreads();
    initCache();
    initSocket(port);
    while(1)
    {
        int src, dest; 
        char buffer[20] = "";
        struct sockaddr_in address; 
        int addrlen = sizeof(address); 
        int server_socket;
        if ((server_socket = accept(server_fd, (struct sockaddr *)&address,  
                       (socklen_t*)&addrlen))<0) 
        { 
            perror("accept"); 
            exit(EXIT_FAILURE); 
        }
        read( server_socket , buffer, 20); 
        sscanf(buffer, "%d %d", &src, &dest);
        assignTask(src, dest, server_socket); 
    }
    return 0;
}

void flushLine(char * line)
{
    int i;
    for(i = 0; i < LINE_SIZE; i++)
    {
        line[i] = '\0';
    }
}

struct Queue* createQueue() {
  struct Queue* q = malloc(sizeof(struct Queue));
  q->items = malloc(NODE_COUNT * sizeof(int));
  q->front = -1;
  q->rear = -1;
  return q;
}

int isEmpty(struct Queue* q) 
{
    if (q->rear == -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }   
}

void enqueue(struct Queue* q, int value) 
{
    if (q->rear == NODE_COUNT - 1)
        printf("\nQueue is Full!!");
    else 
    {
        if (q->front == -1)
        {
            q->front = 0;
        }
        q->rear++;
        q->items[q->rear] = value;
    }
}

int dequeue(struct Queue* q) 
{
	int item;
	if(isEmpty(q)) 
	{		
		printf("Queue is empty");
		item = -1;
	} 
	else 
	{
		item = q->items[q->front];
		q->front++;
		if(q->front > q->rear) 
		{
			q->front = q->rear = -1;
		}
	}
	return item;
}

struct Path * bfs(struct Graph* graph, int srcNode, int destNode) 
{
    int i, nodeFound = 0, firstRun = 1;
    for (i = 0; i < NODE_COUNT; i++) 
    {
        graph->visited[i] = 0;
    }
	struct Queue* queue = createQueue();

    struct Path * path = (struct Path*) malloc(sizeof(struct Path));
    path->node = srcNode;
    path->next = NULL;
    struct Path * tempPath = path;
	graph->visited[srcNode] = 1;
	enqueue(queue, srcNode);

	while (!isEmpty(queue)) 
	{
		int currentNode = dequeue(queue);
		struct Node* temp = graph->adjLists[currentNode];
        if(firstRun)
        {
            firstRun = 0;
        }
        else
        {
            struct Path * new = (struct Path*) malloc(sizeof(struct Path));
            new->node = currentNode;
            new->next = NULL;
            tempPath->next = new;
            tempPath = tempPath->next;
        }
		if(currentNode == destNode)
		{
            nodeFound = 1;
			break;
		}
		while (temp) 
		{
			int adjNode = temp->value;
			if (graph->visited[adjNode] == 0) 
			{
				graph->visited[adjNode] = 1;
				enqueue(queue, adjNode);
			}
			temp = temp->next;
		}
	}
    free(queue->items);
    free(queue);
    if(!nodeFound)
    {
        struct Path* tempFree;
        while (path != NULL)
        {
            tempFree = path;
            path = path->next;
            free(tempFree);
        }
        return NULL;
    }
    else
    {
        return path;
    }
}

struct Node* createNode(int value) {
	struct Node* newNode = malloc(sizeof(struct Node));
	newNode->value = value;
	newNode->next = NULL;
	return newNode;
}

void addEdge(struct Graph* graph, int srcNode, int destNode) {
	struct Node* newNode = createNode(destNode);
	newNode->next = graph->adjLists[srcNode];
	graph->adjLists[srcNode] = newNode;
}

void initGraph()
{
    input_fd = open(inputPath, O_RDONLY);
    char buffer[256];

    int lineCount = 0;
    while(1)
    {
        char line[LINE_SIZE];
        flushLine(line);  
        char character;
        int index = 0;
        int isEOF = 0;
        while(1)
        {
            int val = read(input_fd,&character,1);   //Reading from temp file char by char
            if(val > 0)
            {
                if(character == '\n')               //finished reading the line
                {
                    lineCount++;
                    break;
                }
                else
                {
                    //Success
                    line[index] = character;
                    index++;
                }
            }
            else if(val == 0)           //EOF reached
            {
                isEOF = 1;
                break;
            }
            else                        //ERROR
            {
                fprintf(stderr,"READ ERROR\n");
                exit(-1);
            }
        }
        if(isEOF)
        {
            break;
        }  
        else if(lineCount == 3)
        {
            sscanf(line, "# Nodes: %d Edges: %d", &NODE_COUNT, &EDGE_COUNT);

            graph = malloc(sizeof(struct Graph));

            graph->adjLists = malloc(NODE_COUNT * sizeof(struct node*));
            graph->visited = malloc(NODE_COUNT * sizeof(int));

            int i;
            for (i = 0; i < NODE_COUNT; i++) 
            {
                graph->adjLists[i] = NULL;
                graph->visited[i] = 0;
            }
        }
		else if(lineCount > 4)
		{
			int src, dest;
			sscanf(line, "%d\t%d", &src, &dest);
			addEdge(graph, src, dest);
		}
    }   
    sprintf(buffer, "Graph loaded. Node Count : %d Edge Count : %d\n", NODE_COUNT, EDGE_COUNT);
    write(log_fd, buffer, strlen(buffer));
    memset(buffer, '\0', 256);
    close(input_fd);
}

void initSocket(int port)
{
    struct sockaddr_in address; 
    int sock_opt = 1; 

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
    
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &sock_opt, sizeof(sock_opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( port ); 
    
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
}

void initThreads()
{
    int i;
    workers = (pthread_t *) malloc(currentThreadCount * sizeof(pthread_t));
    sockets = (int *) malloc(currentThreadCount * sizeof(int));
    srcNodes = (int *) malloc(currentThreadCount * sizeof(int));
    destNodes = (int *) malloc(currentThreadCount * sizeof(int));
    workerStatus = (int *) malloc(currentThreadCount * sizeof(int));
    locks = (pthread_mutex_t *) malloc(currentThreadCount * sizeof(pthread_mutex_t));
    /*
    if (pthread_mutex_init(&observer_mutex, NULL) != 0) 
    { 
        printf("\n mutex init has failed\n"); 
        exit(EXIT_FAILURE); 
    }
    if (pthread_mutex_init(&cache_mutex, NULL) != 0) 
    { 
        printf("\n mutex init has failed\n"); 
        exit(EXIT_FAILURE); 
    }
    pthread_mutex_lock(&observer_mutex);
    */
    for(i = 0; i < currentThreadCount; i++)
    {
        int * workerNo = (int *) malloc(sizeof(*workerNo));
        *workerNo = i;
        pthread_create(&workers[i], NULL, requestHandler, workerNo);
        if (pthread_mutex_init(&locks[i], NULL) != 0) 
        { 
            printf("\n mutex init has failed\n"); 
            exit(EXIT_FAILURE); 
        }
        pthread_mutex_lock(&locks[i]);
        workerStatus[i] = 1;
    }
    pthread_create(&observer_tid, NULL, &observer, NULL); 
}

void expandThreadPool()
{
    int newThreadCount = currentThreadCount + (currentThreadCount / 4);
    if(newThreadCount > maxThreadCount)
    {
        newThreadCount = maxThreadCount;
    }
    pthread_t * newWorkers = (pthread_t *) malloc(newThreadCount * sizeof(pthread_t));
    int * newSockets = (int *) malloc(currentThreadCount * sizeof(int));
    int * newSrcNodes = (int *) malloc(currentThreadCount * sizeof(int));
    int * newDestNodes = (int *) malloc(currentThreadCount * sizeof(int));
    int * newWorkerStatus = (int *) malloc(currentThreadCount * sizeof(int));
    for (int i = 0; i < currentThreadCount; i++)
    {
        newWorkers[i] = workers[i];
        newSockets[i] = sockets[i];
        newSrcNodes[i] = srcNodes[i];
        newDestNodes[i] = destNodes[i];
        newWorkerStatus[i] = workerStatus[i];
    }

    for (int i = currentThreadCount; i < newThreadCount; i++)
    {
        int * workerNo = (int *) malloc(sizeof(*workerNo));
        *workerNo = i;
        pthread_create(&newWorkers[i], NULL, requestHandler, workerNo);
    }

    pthread_t * tmpWorkers = workers;
    int * tmpSockets = sockets;
    int * tmpSrcNodes = srcNodes;
    int * tmpDestNodes = destNodes;
    int * tmpWorkerStatus = workerStatus;

    workers = newWorkers;
    sockets = newSockets;
    srcNodes = newSrcNodes;
    destNodes = newDestNodes;
    workerStatus = newWorkerStatus;

    free(tmpWorkers);
    free(tmpSockets);
    free(tmpSrcNodes);
    free(tmpDestNodes);
    free(tmpWorkerStatus);

    currentThreadCount = newThreadCount;
}

void * requestHandler(void* workerNo)
{
    int index = *((int *) workerNo);
    int cacheHit = 0;
    free(workerNo);
    while(1)
    {
        char buffer[256];
        sprintf(buffer, "Thread #%d: waiting for connection\n", index);
        write(log_fd, buffer, strlen(buffer));
        memset(buffer, '\0', 256);
        pthread_mutex_lock(&locks[index]);
        if(isServerShutdown)
            break;
            
        sprintf(buffer, "Thread #%d: searching database for a path from node %d to node %d \n", index, srcNodes[index], destNodes[index]);
        write(log_fd, buffer, strlen(buffer));
        memset(buffer, '\0', 256);
        struct CacheEntry * entry = getPathFromCache(srcNodes[index], destNodes[index]);
        struct Path * path = NULL;
        if(entry)
        {
            path = entry->path;
            cacheHit = 1;
            sprintf(buffer, "Thread #%d: path found in database: ", index);
            write(log_fd, buffer, strlen(buffer));
            memset(buffer, '\0', 256);
        }
        else
        {
            sprintf(buffer, "Thread #%d: no path in database, calculating %d->%d\n", index, srcNodes[index], destNodes[index]);
            write(log_fd, buffer, strlen(buffer));
            memset(buffer, '\0', 256);
            path = bfs(graph, srcNodes[index], destNodes[index]);
            if(path != NULL)
            {
                sprintf(buffer, "Thread #%d: path calculated: ", index);
                write(log_fd, buffer, strlen(buffer));
                memset(buffer, '\0', 256);
            }
            else 
            {
                sprintf(buffer, "Thread #%d: path not possible from node %d to %d  ", index, srcNodes[index], destNodes[index]);
                write(log_fd, buffer, strlen(buffer));
                memset(buffer, '\0', 256);
            }
            struct CacheEntry * newEntry = (struct CacheEntry *) malloc(sizeof(struct CacheEntry));
            newEntry->src = srcNodes[index];
            newEntry->dest = destNodes[index];
            newEntry->path = path;
            insertIntoCache(newEntry);
        }
        if(path == NULL)
        {
            int noPath = -1;
            send(sockets[index] , &noPath , sizeof(noPath) , 0);
        }
        else
        {
            struct Path * temp = path;
            while(temp->next != NULL)
            {
                sprintf(buffer, "%d->", temp->node);
                write(log_fd, buffer, strlen(buffer));
                memset(buffer, '\0', 256);
                send(sockets[index] , &temp->node , sizeof(temp->node) , 0 ); 
                temp = temp->next;
            }
            sprintf(buffer, "%d\n", temp->node);
            write(log_fd, buffer, strlen(buffer));
            memset(buffer, '\0', 256);
            if(cacheHit)
            {
                sprintf(buffer, "Thread #%d: responding to client\n", index);
                write(log_fd, buffer, strlen(buffer));
                memset(buffer, '\0', 256);
            }
            else 
            {
                sprintf(buffer, "Thread #%d: responding to client and adding path to database\n", index);
                write(log_fd, buffer, strlen(buffer));
                memset(buffer, '\0', 256);
            }
            send(sockets[index] , &temp->node , sizeof(temp->node) , 0);
        }
        cacheHit = 0;
        workerStatus[index] = 1;
        currentActiveThreadCount--;
        if(isServerShutdown)
            break;
        //pthread_mutex_unlock(&locks[index]);
    }
}

void assignTask(int src, int dest, int server_socket)
{
    int i;
    char buffer[256];
    for(i = 0; i < currentThreadCount; i++)
    {
        if(workers[i])
        {
            currentActiveThreadCount++;
            sprintf(buffer, "A connection has been delegated to thread id #%d ", i);
            write(log_fd, buffer, strlen(buffer));
            memset(buffer, '\0', 256);
            double percentage = ( (double) currentActiveThreadCount / (double) currentThreadCount ) * 100;
            sprintf(buffer, "system load %%%.2f\n", percentage);
            write(log_fd, buffer, strlen(buffer));
            memset(buffer, '\0', 256);
            pthread_mutex_unlock(&observer_mutex);
            sockets[i] = server_socket;
            srcNodes[i] = src;
            destNodes[i] = dest;
            workerStatus[i] = 0;
            pthread_mutex_unlock(&locks[i]);
            //pthread_mutex_lock(&locks[i]);
            break;
        }
    }
}

void * observer()
{
    //fprintf(stdout, "observer thread started working\n");
    while(1)
    {
        pthread_mutex_lock(&observer_mutex);
        if(isServerShutdown)
            break;
        double percentage = ( (double) currentActiveThreadCount / (double) currentThreadCount ) * 100;
        if(percentage >= 75.0 && currentThreadCount < maxThreadCount)
            expandThreadPool();

    }
}

void freeResources()
{
    int i;
    free(workers);
    free(sockets);
    free(srcNodes);
    free(destNodes);
    free(workerStatus);
    free(locks); 
    free(graph->visited);
    for(i = 0; i < NODE_COUNT; i++)
    {
        struct Node* head = graph->adjLists[i];
        struct Node* temp;
        while (head != NULL)
        {
            temp = head;
            head = head->next;
            free(temp);
        }
    }
    free(graph->adjLists);
    free(graph);
    clearCache();
}

void initCache()
{
    int i;
    for(i = 0; i < CACHE_SIZE; i++)
    {
        cache_DB[i] = NULL;
    }
}

int calculateCacheHash(int src, int dest)
{
    return ((src * 2767) + (dest * 2767)) % CACHE_SIZE;
}

struct CacheEntry * getPathFromCache(int src, int dest)
{
    int index = calculateCacheHash(src, dest);
    pthread_mutex_lock(&cache_mutex);
    pthread_mutex_unlock(&cache_mutex);
    if(cache_DB[index] == NULL || cache_DB[index]->src != src || cache_DB[index]->dest != dest)
    {
        return NULL;
    }
    return cache_DB[index];
}

void insertIntoCache(struct CacheEntry * entry)
{
    pthread_mutex_lock(&cache_mutex);
    int index = calculateCacheHash(entry->src, entry->dest);
    if(cache_DB[index])
    {
        struct Path * path = cache_DB[index]->path;
        struct Path * temp;
        while (path != NULL)
        {
            temp = path;
            path = path->next;
            free(temp);
        }
    }
    cache_DB[index] = entry;
    pthread_mutex_unlock(&cache_mutex);
}

void clearCache()
{
    int i;
    for(i = 0; i < CACHE_SIZE; i++)
    {
        if(cache_DB[i])
        {
            struct Path * path = cache_DB[i]->path;
            struct Path * temp;
            while (path != NULL)
            {
                temp = path;
                path = path->next;
                free(temp);
            }
        }
        free(cache_DB[i]);
    }
}
