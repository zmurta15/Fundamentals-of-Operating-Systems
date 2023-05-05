#include "log.h"

#include <stdio.h>
#include <pthread.h>

void fsolog(const char* message) {
	printf("[%p]: %s\n", pthread_self(), message);
}