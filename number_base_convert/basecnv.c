#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "basecnvlib.h"


// params with a : after it requre an additional argument
static const char *optstring = "i:numo:";

void printHelp() {
	printf("\nBase conversion\nUsage:\n");
	printf("-i: input base\n-o: output base\ninput number\n");
	printf("Bases supported: decimal, binary, octal, hexadecimal\n");
	printf("eg. basecnv -i decimal -o octal 10\n\n");
}

int main(int argc, char *argv[]) {
	if(argc == 2 || argc < 6 || argc > 6 ) {
		printHelp();
		exit(0);
	}
	struct args arg_struct;
	int op =  getopt(argc, argv, optstring);
	while( op != -1 ) {
		switch(op) {
			case 'i': arg_struct.bin = optarg; break;
			case 'o': arg_struct.bout = optarg; break;
			default: printf("Too few parameters recieved"); printHelp(); exit(-1);
		}
		op = getopt(argc, argv, optstring);	
	}
	argc -= optind;
	argv += optind;

	if( argc > 1 ) {
		printf("Error: Too many parameters recieved\n");
		printHelp();
		exit(-1);
	}

	arg_struct.num_in	 = argv[0];

	printf("\nbin: %s bout: %s num_in: %s, num_out: %s\n", arg_struct.bin, arg_struct.bout, arg_struct.num_in, arg_struct.num_out);

	convBase(&arg_struct);

	printf("\nbin: %s bout: %s num_in: %s, num_out: %s\n", arg_struct.bin, arg_struct.bout, arg_struct.num_in, arg_struct.num_out);
	return 0;
}