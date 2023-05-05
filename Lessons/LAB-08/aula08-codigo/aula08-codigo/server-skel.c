#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


#include "udp_comm.h"

#define BUFSIZE 1024



void server(int port){

	// opens UDP port
	sd = UDP_Open( port);
	if( sd < 0) {
		perror("");
		return;
	}
	else{

	// a preencher

	
	}		
}


int main( int argc, char *argv[]){

	int port;
	
	if( argc == 2){
		port = atoi(argv[1]);
	}
	else{
		printf("Usage: %s port\n", argv[0]);
		return 1;
	}

	server(port);
	return 0;
}

