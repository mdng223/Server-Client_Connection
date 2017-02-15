//
//  mcget.cpp
//  
//
//  Created by Mark Daniel Ng on 11/20/16.
//
//

//#include "mcget.hpp"
#include "csapp.h"
#include "mycloud.h"
int main( int argc, char *argv[] ){

	uint32_t port, key, type;
        type = 0;
        char *host, *filename, data[MAXLINE];
	//test for correct input
        if (argc != 5) {
                fprintf(stderr, "Usage: <%s> <host> <port> <SecretKey> <filename> \n", argv[0]);
                exit(1);
        }
        host = argv[1]; port = atoi(argv[2]); key = atoi(argv[3]); filename = argv[4];


	mycloud_getfile(type, host, port, key, filename, data, strlen(data));
	return 0;
}

