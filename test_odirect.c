/*
 * Author: Diego Cordoba - @d1cor, based on linuxito.com initial version.
 * Test if a filesystem supports O_DIRECT flag
 * Usage: ./progname path_file
 * where path_file is a file stored in a convinient filesystem.
 * Compilation: gcc test_odirect.c -o test_odirect
*/


#define _GNU_SOURCE

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

void usage(char* progname);

int main(int argc, char** argv) {

	char *file = *(argv+1);

	// test correct arguments
	if(argc!=2) usage(*argv);

	// try open file
	int fd = open(file,O_DIRECT|O_RDWR);

	// if error
	if(fd<0){
		// if error is "invalid argument" (see "man 2 open" errors section):
		if(errno == EINVAL){
			printf("O_DIRECT not supported on filesystem.\n");
		}else{
			fprintf(stderr,"%d - %s\n", errno, strerror(errno));
		}
		_exit(2);
	}

	printf("O_DIRECT supported!\n");
	close(fd);

	return 0;

}


void usage(char* progname){
	fprintf(stderr, "\nUSAGE:\n\t%s <path_file>\n\n", progname);
	_exit(1);
}
