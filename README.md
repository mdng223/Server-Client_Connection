# server_client
Server-Client connection written in C. Able to add, edit, delete, and list files. 


Members: Daniel Ng, Chiu Tsang


Files Included:
	- README:	this file
	- csapp.c	functions to read and write from/to server
	- csapp.h	header file for csapp.c
	- mcdel.c 	delete a file from the server
	- mclist.c	lists files from the server
	- mcget.c	retrieves file from server and prints out its data
	- mcput.cpp	writes a file onto the server
	- mycloud.c	library/api calls
	- server.c	Accepts client-side application calls and manipulates data
	- Makefile	



How to compile:
		make

How to clean:
		make clean

How to get files:
		./mcget <host> <port> <SecretKey> <filename>

How to put (write) files:
		./mcput <host> <port> <secretKey> <filename>

How to delete files:
		./mcdel <host> <port> <secretKey> <filename>

How to list files:
		./mclist <host> <port> <secretKey>

