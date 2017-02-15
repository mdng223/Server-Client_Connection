CFLAGS = -Wall -g
CPPFLAGS = -Wall

all: mcput mcget mcdel mclist server

csapp.h:
	wget http://csapp.cs.cmu.edu/2e/ics2/code/include/csapp.h

csapp.c:
	wget http://csapp.cs.cmu.edu/2e/ics2/code/src/csapp.c

csapp.o: csapp.h csapp.c



server: server.c csapp.c
	gcc $(CFLAGS) server.c csapp.c -lpthread -o server

mcput: mcput.c csapp.o 
	gcc $(CFLAGS) mcput.c mycloud.c csapp.c -lpthread -o mcput

mcget: mcget.c csapp.o
	gcc $(CPPFLAGS) mcget.c csapp.o mycloud.c -lpthread -o mcget

mcdel: mcdel.c csapp.o
	gcc $(CPPFLAGS) mycloud.c mcdel.c csapp.o -lpthread -o mcdel

mclist: mclist.c csapp.o
	gcc $(CPPFLAGS) mclist.c mycloud.c csapp.o -lpthread -o mclist

.PHONY: clean
clean:
	/bin/rm -rf csapp.h csapp.c *.o server mcput mcget mcdel mclist client
