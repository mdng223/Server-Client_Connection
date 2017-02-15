//
//  mycloud.c
//  
//
//  Created by Mark Daniel Ng on 11/27/16.
//
//

#include "mycloud.h"



rio_t rio;
int MAXDATA = 100*1024;
int clientfd;


int mycloud_putfile(uint32_t type, char *MachineName, uint32_t TCPport, uint32_t SecretKey, char *Filename, char *data, uint32_t datalen){

	/* 	Connect to server	*/
	clientfd = Open_clientfd( MachineName, TCPport);	
	Rio_readinitb(&rio, clientfd);	
	int server_success = -1;
	char line[MAXLINE];
	strcpy(line,"");
	datalen = strlen(data);
	/* 	Pass data to Server	*/
	SecretKey = htonl(SecretKey);
	Rio_writen( clientfd, &SecretKey, 4);	
	type = htonl(type);
	Rio_writen( clientfd, &type, 4);

	Rio_writen( clientfd, Filename, 80);
	datalen = htonl(datalen);
	while (Fgets(line, MAXLINE, stdin) != NULL) { // more input
		strcat(data, line); 
	}


	datalen = strlen(data);
	datalen = htonl(datalen);	
	Rio_writen( clientfd, &datalen, 4);	
	datalen = strlen(data);
	Rio_writen( clientfd, data, datalen);
	/* 	End Pass data to server */


	/*	Receive Data from server */
	Rio_readnb(&rio, &server_success, 4);
	server_success = htonl(server_success);


	if(server_success == 0)
		printf("Put request successful. \n");	
	else if(server_success == -1)
		printf("Put request failed. \n");
	/*------------------------------- */

	return 0;
}

int mycloud_getfile(uint32_t type, char *MachineName, uint32_t TCPport, uint32_t SecretKey, char *Filename, char *data, uint32_t datalen){
	clientfd = Open_clientfd( MachineName, TCPport);	
	Rio_readinitb(&rio, clientfd);	
	uint32_t server_success = 3;
	uint32_t bytes;

	/* 	Pass data to Server	*/
	SecretKey = htonl(SecretKey);
	Rio_writen( clientfd, &SecretKey, 4);	
	type = htonl(type);
	Rio_writen( clientfd, &type, 4);
	Rio_writen( clientfd, Filename, 80);
	/*------------------------------*/	

	/*	Receive Data from server */
	Rio_readnb(&rio, &server_success, 4);
	server_success = htonl(server_success);


	/*------------------------------- */
	if(server_success == 0){
		Rio_readnb(&rio, &bytes, 4);
		bytes = htonl(bytes);
		Rio_readnb(&rio, data, bytes);
		printf("Get request successful. \n");	
		printf("%s has %d number of bytes.\n", Filename, bytes);
		printf("Contents of %s: %s\n", Filename, data);
	}
	else if(server_success == -1)
		printf("Get request failed. \n");
	else
		printf("Invalid secret key. \n");	


	return 0;
}

int mycloud_delfile(uint32_t type, char *MachineName, uint32_t TCPport, uint32_t SecretKey, char *Filename){
	int server_success = 2;
	clientfd = Open_clientfd( MachineName, TCPport);	
	Rio_readinitb(&rio, clientfd);	
	/* 	Pass data to Server	*/
	SecretKey = htonl(SecretKey);
	Rio_writen( clientfd, &SecretKey, 4);	
	type = htonl(type);
	Rio_writen( clientfd, &type, 4);
	Rio_writen( clientfd, Filename, 80);
	/*------------------------------*/	




	/*	Receive Data from server */
	Rio_readnb(&rio, &server_success, 4);
	/*------------------------------*/	

	if(server_success == 0)
		printf("%s successfully deleted.\n", Filename);
	else if(server_success == -1)
		printf("Failed.\n");
	else
		printf("Unexpected result.\n");

	return 0;
}


int mycloud_listfiles(uint32_t type, char *MachineName, uint32_t TCPport, uint32_t SecretKey, char *listbuf, uint32_t listbuflen){
//	char *Filename;
	int server_success = 2;
	clientfd = Open_clientfd( MachineName, TCPport);	
	Rio_readinitb(&rio, clientfd);	
	/* 	Pass data to Server	*/
	SecretKey = htonl(SecretKey);
	Rio_writen( clientfd, &SecretKey, 4);	
	type = htonl(type);
	Rio_writen( clientfd, &type, 4);

	/*------------------------------*/	

	
	/*	Receive Data from server */

	Rio_readnb(&rio, &server_success, 4);
	server_success = htonl(server_success);



	if(server_success == 0){
		Rio_readnb(&rio, &listbuflen, 4);
		listbuflen = htonl(listbuflen);
		Rio_readnb(&rio, listbuf, listbuflen); 
		printf("List request successful. \n");	
		printf("Total length of file names = %d\n", listbuflen);
		printf("File names: %s\n", listbuf); 
	}
	else if(server_success == -1)
		printf("List request failed. \n");



	/*------------------------------- */


	return 0;
}
