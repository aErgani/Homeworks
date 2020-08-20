all:
	gcc -c -Wall server.c
	gcc -c -Wall client.c
	gcc -o server server.o -lrt -lpthread
	gcc -o client client.o

clean:
	rm server
	rm server.o
	rm client
	rm client.o