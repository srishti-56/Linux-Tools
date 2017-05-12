#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_SIZE 9999

struct args {
	char *bin;
	char *bout;
	char *num;
};
// params with a : after it requre an additional argument
static const char *optstring = "i:numo:";

int main(int argc, char *argv[]) {
	struct args arg_struct;
	int op = getopt(argc, argv, optstring);
	while( op != -1 ) {
		switch(op) {
			case 'i': arg_struct.bin = optarg; break;
			case 'o': arg_struct.bout = optarg; break;
			default: printf("Too few parameters recieved"); exit(-1);
		}
		op = getopt(argc, argv, optstring);	
	}
	argc -= optind;
	argv += optind;

	if( argc > 1 ) {
		printf("Too many parameters recieved\n");
		exit(-1);
	}

	arg_struct.num = argv[0];
	
	printf("\nbin: %s bout: %s num: %s\n", arg_struct.bin, arg_struct.bout, arg_struct.num);

	return 0;
}