//
//  mycloud.h
//  
//
//  Created by Mark Daniel Ng on 11/27/16.
//
//

#ifndef mycloud_h
#define mycloud_h
#include "csapp.h"
#include <stdio.h>
#include <stdint.h>
#endif /* mycloud_h */

//universal get input function protocol
int a(char *MachineName, uint32_t TCPport, uint32_t key, uint32_t reqtype, char *Filename);

//mcput function protocol
int mycloud_putfile(uint32_t type, char *MachineName, uint32_t TCPport, uint32_t SecretKey, char *Filename, char *data, uint32_t datalen);

//mcget function protocol
int mycloud_getfile(uint32_t type, char *MachineName, uint32_t TCPport, uint32_t SecretKey, char *Filename, char *data, uint32_t datalen);

//mcdel function protcol
int mycloud_delfile(uint32_t type, char *MachineName, uint32_t TCPport, uint32_t SecretKey, char *Filename);

//mclist function protocol
int mycloud_listfiles(uint32_t type, char *MachineName, uint32_t TCPport, uint32_t SecretKey, char *listbuf, uint32_t listbuflen);

