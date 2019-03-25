main:	server client

server:	server.o
	gcc server.o -o server

server.o: server.c shared.h
	gcc -Wall -c server.c

client: client.o
	gcc client.o -o client

client.c: client.c shared.h
	gcc -Wall -c client.c

clean:
	rm server server.o client client.o
