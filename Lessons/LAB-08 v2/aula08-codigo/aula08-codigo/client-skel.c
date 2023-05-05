#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "udp_comm.h"

#define BUFSIZE 1024




int main( int argc, char *argv[]){

	int port;
	
	if( argc == 5){
		port = argv[1];
		int udp = UDP_Open(port +1);
		char[20] = strcat()
	}
	else{
		printf("Usage: %s hostname port nomeProgama argumento\n", argv[0]);
		return 1;
	}
	
	// ....
	
	return 0;
}

