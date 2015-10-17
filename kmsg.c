#include "kmsg.h"

int kmsg_fd;

int kmsg_open(void) {
	kmsg_fd = open("/dev/kmsg", O_RDONLY | O_NONBLOCK);
	if (kmsg_fd < 0) {
		printf("failed to open /dev/kmsg\n");
		return 1;
	}

	return 0;
}

int kmsg_read(char *buffer, int buffer_size) {
	ssize_t bytes_read;
	while (1) {
		bytes_read = read(kmsg_fd, buffer, buffer_size);
		if (bytes_read < 0) {
			if (bytes_read == EAGAIN) {
				break;
			} else if (bytes_read == EPIPE) {
				continue;
			} else {
				printf("failed to read /dev/kmsg\n");
				return 1;
			}
		} else if (bytes_read < buffer_size) {
			// cut away newline
			buffer[bytes_read-1] = '\0';
			break;
		}
	}
	return 0;
}

void kmsg_close(void) {
	close(kmsg_fd);
}
