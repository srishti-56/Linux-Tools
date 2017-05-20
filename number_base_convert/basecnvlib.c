#include <stdio.h>
#include "basecnvlib.h"
#include <string.h>

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

struct args* decConv(struct args *arg_struct) {
	if(!strcmp(arg_struct->bout, "binary"))
	
	else if(!strcmp(arg_struct->bout, "hexadecimal"))
	
	else if(!strcmp(arg_struct->bout, "octal"))
	
	return arg_struct;
}

struct args* binConv(struct args *arg_struct) {
	
	return arg_struct;
}

struct args* hexadecConv(struct args *arg_struct) {
	
	return arg_struct;
}

struct args* octConv(struct args *arg_struct) {
	
	return arg_struct;
}