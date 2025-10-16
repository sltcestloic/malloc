#include "malloc.h"
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t g_malloc_mutex = PTHREAD_MUTEX_INITIALIZER;

void *malloc(size_t size) {
	write(1, "malloc called\n", 14);
	void *ptr = NULL;
	pthread_mutex_lock(&g_malloc_mutex);
	size = (size + 15) & ~15;
	char buf[32];
	int len = snprintf(buf, sizeof(buf), "malloc(%zu)\n", size);
	write(1, buf, len);
	pthread_mutex_unlock(&g_malloc_mutex);
	return ptr;
}