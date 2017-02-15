//
//  mclist.cpp
//  
//
//  Created by Mark Daniel Ng on 11/20/16.
//
//

//#include "mclist.hpp"
#include "csapp.h"
#include "mycloud.h"


int main( int argc, char *argv[] ){
	uint32_t port, key, type;
	type = 3;
	char *host, data[MAXLINE];
	//test for correct input
	if (argc != 4) {
		fprintf(stderr, "Usage: <%s> <host> <port> <SecretKey> \n", argv[0]);
		exit(1);
	}
	host = argv[1]; port = atoi(argv[2]); key = atoi(argv[3]);


	mycloud_listfiles(type, host, port,  key, data, strlen(data));
	return 0;
}

