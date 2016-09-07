CC = gcc -Wall -O1 -g
LDFLAGS = -lpthread

all: server client


server: server.c server_util.h server_util.c utility.h struct_util.c  
	$(CC) -o server server.c struct_util.c server_util.c $(LDFLAGS)

client: client.c client_util.h client_util.c utility.h
	$(CC) -o client client.c client_util.c


runS:
	./server

runC:
	./client 

:phony

clean:

	rm -f server client
