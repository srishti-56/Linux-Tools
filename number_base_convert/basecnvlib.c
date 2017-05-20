// any number is first converted to decimal, after which decimal converted to -o param

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

	else if(!strcmp(arg_struct->bout, "octal")) {
		int t = atoi( arg_struct->num_in );
		char *t_cc;
		while( t != 0 ) {
			arg_struct->num_out = (char *) realloc(arg_struct->num_out, sizeof(arg_struct->num_out) + 1);
			t_cc = (char *) realloc(t_cc, sizeof(arg_struct->num_out));	
			int t_c = t % 8;
			sprintf(t_cc, "%d", t_c);
			strcat(arg_struct->num_out, t_cc);
			t /= 8;
		}
		//free(t_cc);
		// strrev does not exist in linux string.h
		arg_struct->num_out = reverseString(arg_struct->num_out);
		return arg_struct;
	}


	// to hexadecimal
	else if(!strcmp(arg_struct->bout, "hexadecimal")) {
		int t = atoi( arg_struct->num_in );
		char *t_cc;
		while( t != 0 ) {
			arg_struct->num_out = (char *) realloc(arg_struct->num_out, sizeof(arg_struct->num_out) + 1);
			
			// ### Why is this giving a memory error?
			t_cc = (char *) realloc(t_cc, sizeof(arg_struct->num_out));	
			// ######################################
			
			int t_c = t % 16;
			printf("%d\n", t_c);
			if( t_c <= 9 ) {
				sprintf(t_cc, "%d", t_c);
			}
			else {
				char temp_h;
				switch(t_c) {
					case 10: temp_h = 'A'; break;
					case 11: temp_h = 'B'; break;
					case 12: temp_h = 'C'; break;
					case 13: temp_h = 'D'; break;
					case 14: temp_h = 'E'; break;
					case 15: temp_h = 'F'; break;
				}
				sprintf(t_cc, "%d", sprintf(t_cc, "%d", t_c));
			}

			strcat(arg_struct->num_out,  t_cc);
			t /= 16;
		}
		// strrev does not exist in linux string.h
		arg_struct->num_out = reverseString(arg_struct->num_out);
		return arg_struct;
	}

	return arg_struct;
}


// binary - convert to decimal
struct args* binConv(struct args *arg_struct) {
	// convert to decimal for input value num_in, then call decConv which will take decimal and convert
	return arg_struct;
}


// hexadecimal - convert to decimal
struct args* hexadecConv(struct args *arg_struct) {
	// convert to hexadecimal for input value num_in, then call decConv which will take decimal and convert
	return arg_struct;
}


// octal - convert to decimal
struct args* octConv(struct args *arg_struct) {
	// convert to octal for input value num_in, then call decConv which will take decimal and convert
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