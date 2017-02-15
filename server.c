/* 
 * echoserveri.c - An iterative echo server 
 */ 
/* $begin echoserverimain */



#include "csapp.h"



/*	Server Data in memory		*/
struct server_data{
	char name[81];
	char data[MAXLINE];
	uint32_t length;
};

/*	Server Output Variables 	*/
struct client_input{
	char *filename;
	char *opstatus;
	char *reqtype;
};


int main(int argc, char **argv) {
	int 		listenfd, connfd, ctr = 0;
	uint32_t 	key, clientkey, reqtype, port, n;
	socklen_t 	clientlen;
	struct 		sockaddr_in clientaddr;
	char *filename = malloc(81);
	char *client_data = malloc(MAXLINE);

	struct server_data	server_data[1000];	

	rio_t		rio;

	struct client_input 	client_input;



	if (argc != 3) {

		fprintf(stderr, "usage: %s <port> <secretkey>\n", argv[0]);
		exit(0);
	}
	port = atoi(argv[1]); key = atoi(argv[2]); 


	listenfd = Open_listenfd(port);
	while (1) {
		
		clientlen = sizeof(clientaddr);
		connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
		Rio_readinitb(&rio, connfd);

		/* 	client key 	*/
		Rio_readnb(&rio, &clientkey, 4);
		clientkey = ntohl(clientkey);

		/* 	Request type 	*/
		Rio_readnb(&rio, &reqtype, 4);
		reqtype = ntohl( reqtype );






		if(reqtype == 0){

			/*	File name	*/
			Rio_readnb(&rio, filename, 80);
			client_input.reqtype = "get";
			int i = 0;
			int bytes;
			int success = 0;
			char *stuff;
			int flag = 0;
			if(clientkey == key){
				while(i < ctr){

					if(strcmp( filename, server_data[i].name) == 0){
						success = ntohl(success);
						Rio_writen( connfd, &success, 4);

						bytes = server_data[i].length;	
						bytes = ntohl(bytes);	

						Rio_writen( connfd, &bytes, 4); 
						bytes = strlen(server_data[i].data);


						stuff = server_data[i].data;

						Rio_writen( connfd, stuff, bytes); 
						flag = 1;

					}
					i = i + 1;
				}
				if( flag == 0 ){
					client_input.opstatus = "error";
					success = -1;
					success = ntohl(success);
					Rio_writen( connfd, &success, 4);

				}
				else
					client_input.opstatus = "success";
			}
			else{
				success = -1;
				client_input.opstatus = "error";	
				success = ntohl(success);
				Rio_writen( connfd, &success, 4);

			}


		}
		else if(reqtype == 1){
                        client_input.reqtype = "put";
			int success = 0, j = 0, overwriteflag = 0;

			/*	File name	*/
			Rio_readnb(&rio, filename, 80);
			/*	File bytes	*/
			Rio_readnb(&rio, &n, 4);
			n = ntohl( n ); 
			/*	File Data 	*/
			Rio_readnb(&rio, client_data, n);

			if(clientkey == key){
				if(j == ctr){ 
					strcpy(server_data[ctr].name, filename);	
					strcpy(server_data[ctr].data, client_data);
					server_data[ctr].length	= n;
				}
				else if (j < ctr){
					while(j < ctr){
						if(strcmp( filename, server_data[j].name ) == 0){
							strcpy(server_data[j].name, filename);	
							strcpy(server_data[j].data, client_data);
							server_data[j].length	= n;
							overwriteflag = 1;	
						}
						j = j + 1;

					} 
					if(overwriteflag == 0){
						strcpy(server_data[ctr].name, filename);	
						strcpy(server_data[ctr].data, client_data);
						server_data[ctr].length	= n;
					}
				}


				ctr = ctr + 1;
				client_input.opstatus = "success";
				success = 0;
			}
			else{
				client_input.opstatus = "error";
				success = -1;
			}
			success = ntohl(success);
			Rio_writen( connfd, &success, 4);
		}
		else if(reqtype == 2){
			char *file_name = malloc(MAXLINE);	
			int k = 0, status = -1, flag = 0;
                        client_input.reqtype = "delete";

			/*	File Data 	*/
			Rio_readnb(&rio, file_name, 80);
			strcpy(filename, file_name);
			

			if(clientkey == key){		
				if(k == ctr){
					status = -1;
				}
				else if( k < ctr){
					while(k < ctr){
						if(strcmp( file_name, server_data[k].name) == 0){
							strcpy(server_data[k].name, "");
							strcpy(server_data[k].data, "");
							server_data[k].length = 0;
							flag = 1;
							status = 0;
							client_input.opstatus = "success";
						}
						k = k + 1;
					}	
				}
				else
					printf("unexpected result \n");

				if(flag == 0){
					client_input.opstatus = "error";
					status = -1;
				}
			}
			else{
				client_input.opstatus = "error";

			}

			status = ntohl(status);
			Rio_writen( connfd, &status, 4);
		}
		else if(reqtype == 3 ){
			int i = 0, byte_ctr = 0, success = 0;
			char *file_names = malloc(MAXLINE);	
                        client_input.reqtype = "list";
			filename = "NONE";

			if(clientkey == key){
				while(i < ctr){

					byte_ctr = byte_ctr + strlen(server_data[i].name);
					if(strlen(server_data[i].name) == 0){
						strcat(file_names, server_data[i].name);
					}
					else{
						strcat(file_names, "\n");
						strcat(file_names, server_data[i].name);
						byte_ctr = byte_ctr + 1;
					}
					i = i + 1;
				}
				client_input.opstatus = "success";
				success = ntohl(success);
				Rio_writen( connfd, &success, 4);
				byte_ctr = ntohl(byte_ctr);
				Rio_writen( connfd, &byte_ctr, 4);
				byte_ctr = strlen(file_names);
				Rio_writen( connfd, file_names, byte_ctr); 
			}
			else{
				success = -1;
				client_input.opstatus = "error";
				success = ntohl(success);
				Rio_writen( connfd, &success, 4);
			}
		
			exit(0);
	
				
		}
		else if( clientkey != key){
			if(reqtype == 0)
				client_input.reqtype = "get";
			else if(reqtype == 1)
				client_input.reqtype = "put";
			else if(reqtype == 2)
				client_input.reqtype = "delete";
			else if(reqtype == 3)
				client_input.reqtype = "list";
			else
				client_input.reqtype = "error";
				
			/*	File name	*/
			Rio_readnb(&rio, filename, 80);
			client_input.opstatus = "failed";
		}
		else
			client_input.opstatus = "error";


		printf("Secret Key = \t\t%d \n", clientkey);
		printf("Request Type = \t\t%s\n", client_input.reqtype);
		printf("Filename = \t\t%s \n", filename);
		printf("Operation Status = \t%s\n", client_input.opstatus);
		printf("-------------------------------\n");

		Close(connfd);

	}


}
/* $end echoserverimain */

