#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

int kmsg_open(void);
int kmsg_read(char*, int);
void kmsg_close(void);
