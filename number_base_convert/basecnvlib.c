#include <stdio.h>
#include "basecnvlib.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct args* convBase(struct args *arg_struct) {
	if(!strcmp(arg_struct->bin, "decimal"))
		decConv(arg_struct);
	else if(!strcmp(arg_struct->bin, "binary"))
		binConv(arg_struct);
	else if(!strcmp(arg_struct->bin, "hexadecimal"))
		hexadecConv(arg_struct);
	else if(!strcmp(arg_struct->bin, "octal"))
		octConv(arg_struct);
	
	return arg_struct;
}

// decimal
struct args* decConv(struct args *arg_struct) {
	
	// to binary
	if(!strcmp(arg_struct->bout, "binary")) {
		int t = atoi( arg_struct->num_in );
		
		if(t == 0) {
			arg_struct->num_out = "0";
			return arg_struct;
		}
		if(t == 1) {
			arg_struct->num_out = "1";
			return arg_struct;
		}

		while( t != 0 ) {
			arg_struct->num_out = (char *) realloc(arg_struct->num_out, sizeof(arg_struct->num_out) + 1);	
			t % 2 == 0 ? strcat(arg_struct->num_out, "0") : strcat(arg_struct->num_out, "1");
			t /= 2;
		}
		// strrev does not exist in linux string.h
		arg_struct->num_out = reverseString(arg_struct->num_out);
		return arg_struct;
	}
	
	// to hexadecimal
	else if(!strcmp(arg_struct->bout, "hexadecimal"))
		return arg_struct;
	// to octal
	else if(!strcmp(arg_struct->bout, "octal"))
		return arg_struct;

	return arg_struct;
}

// binary
struct args* binConv(struct args *arg_struct) {
	
	return arg_struct;
}

// hexadecimal
struct args* hexadecConv(struct args *arg_struct) {
	
	return arg_struct;
}

// octal
struct args* octConv(struct args *arg_struct) {
	
	return arg_struct;
}

char* reverseString(char *str) {
	char *p1, *p2;

    if (! str || ! *str)
        return str;
    for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2) {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }

      return str;
}