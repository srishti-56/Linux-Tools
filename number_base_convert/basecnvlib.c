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
	
	// to hexadecimal
	else if(!strcmp(arg_struct->bout, "hexadecimal")) {
		int t = atoi( arg_struct->num_in );
		
		while( t != 0 ) {
			arg_struct->num_out = (char *) realloc(arg_struct->num_out, sizeof(arg_struct->num_out) + 1);	
			// + 48 -> put into ascii range
			// char -> char * for strcat
			char t_c = t % 16;

			if( t_c <= 9 ) {
				t_c += 48;
				t_c = (char) t_c;
			}
			else {
				switch(t_c) {
					case 10: t_c = 'A'; break;
					case 11: t_c = 'B'; break;
					case 12: t_c = 'C'; break;
					case 13: t_c = 'D'; break;
					case 14: t_c = 'E'; break;
					case 15: t_c = 'F'; break;
				}
			}

			// ################ BUG HERE ################
			char *t_cc = &t_c;
			printf("%s\n", t_cc);
			// ##########################################

			strcat(arg_struct->num_out,  t_cc );
			t /= 16;
			//printf("\n***t_c: %c t_cc: %s num_out: %s***\n", t_c, t_cc, arg_struct->num_out);
		}
		// strrev does not exist in linux string.h
		arg_struct->num_out = reverseString(arg_struct->num_out);
		return arg_struct;
	}
	

	// to octal
	else if(!strcmp(arg_struct->bout, "octal")) {
		int t = atoi( arg_struct->num_in );
		while( t != 0 ) {
			arg_struct->num_out = (char *) realloc(arg_struct->num_out, sizeof(arg_struct->num_out) + 1);	
			// + 48 -> put into ascii range
			// char -> char * for strcat
			char t_c = (char) t % 8 + 48;
			char *t_cc = &t_c;
			strcat(arg_struct->num_out,  t_cc );
			t /= 8;
		}
		// strrev does not exist in linux string.h
		arg_struct->num_out = reverseString(arg_struct->num_out);
		return arg_struct;
	}

	return arg_struct;
}


// binary - convert to decimal
struct args* binConv(struct args *arg_struct) {
	
	return arg_struct;
}


// hexadecimal - convert to decimal
struct args* hexadecConv(struct args *arg_struct) {
	
	return arg_struct;
}


// octal - convert to decimal
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