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
#include <arpa/inet.h> 

char * ipAddress;
int port;
int srcNode;
int destNode;

void signal_handler(int signum)     //Handles SIGINT signal
{
    
}

int main(int argc, char *argv[])
{
    if(argc < 3)
    {
        printf("Invalid argument count.\nNeeded 4 labeled argument. -a for ip address -p for port number -s for source node -d for destination node.\nTerminating...\n");
        exit(-1); 
    }

    int opt;
    while((opt = getopt(argc,argv,"a:p:s:d:")) != -1)
    {  
        switch(opt)  
        {   
            case 'a':  
                fprintf(stdout,"IP Address: %s\n", optarg);  
                ipAddress = optarg;
                break;  
            case 'p':  
                fprintf(stdout,"Port: %s\n", optarg);  
                port = atoi(optarg);
                break;  
            case 's':  
                fprintf(stdout,"Source Node: %s\n", optarg);  
                srcNode = atoi(optarg);
                break;  
            case 'd':  
                fprintf(stdout,"Destination Node: %s\n", optarg);  
                destNode = atoi(optarg);
                break;  
            default:  
                fprintf(stderr,"unknown option: '%c' Needed 4 labeled argument. -a for ip address -p for port number -s for source node -d for destination node.\nTerminating...\n", opt);
                exit(-1);  
        }  
    }

    int client_socket = 0; 
    struct sockaddr_in serv_addr; 
    char message[20]; 
    sprintf(message, "%d %d", srcNode, destNode);
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(port); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, ipAddress, &serv_addr.sin_addr) <= 0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
    fprintf(stdout, "Client (%d) connecting to %s:%d \n", port, ipAddress, port); 
    if (connect(client_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
    send(client_socket , message , strlen(message) , 0 ); 
    fprintf(stdout, "Client (%d) connected and requesting a path from node %d to %d\n", port, srcNode, destNode); 
    fprintf(stdout, "Server’s response to (%d): ", port); 
    while(1)
    {
        int node;
        read( client_socket , &node, sizeof(node)); 
        if(node == -1)
        {
            fprintf(stdout, "Server’s response (%d): NO PATH\n", port);
            break;
        }
        if(node == destNode)
        {
            fprintf(stdout, "%d\n", node);
            break;
        }
        else
        {
            fprintf(stdout, "%d->", node); 
        }
        
    }
    return 0;
}