# server_client
* Establishes a server-client connection to different hosts and ports.
* Able to add, edit, delete, and list files. 
* Requires a key to be able to manipulate data.



### Files Included:
	* **README:**	- this file
	* **csapp.c**	- functions to read and write from/to server
	* **csapp.h**	- header file for csapp.c
	* **mcdel.c** 	- delete a file from the server
	* **mclist.c**	- lists files from the server
	* **mcget.c**	- retrieves file from server and prints out its data
	* **mcput.cpp**	- writes a file onto the server
	* **mycloud.c**	- library/api calls
	* **server.c**	- Accepts client-side application calls and manipulates data
	* **Makefile**	

## Authors

* **Daniel Ng** - [mdng223](https://github.com/mdng223)
* **Gary Tsang**

## How to compile:
		make

## How to clean:
		make clean

## How to get files:
		./mcget <host> <port> <SecretKey> <filename>

## How to put (write) files:
		./mcput <host> <port> <secretKey> <filename>

## How to delete files:
		./mcdel <host> <port> <secretKey> <filename>

## How to list files:
		./mclist <host> <port> <secretKey>

