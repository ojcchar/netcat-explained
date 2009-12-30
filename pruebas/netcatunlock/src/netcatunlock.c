/*
 ============================================================================
 Name        : netcatunlock.c
 Author      : tuareg,ojcchar
 Version     :
 Copyright   : copyright UNLock
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

void printUsage();

int main(int argc, char *argv[]) {
	short var ;

	if(argc<3){
		printUsage();
		return EXIT_SUCCESS;
	}


	puts("These are the arguments:");
	//puts((const char*)argc);
	for (var = 1; var < argc; ++var) {
		//puts((char)var);
		puts(argv[var]);
	}

	return EXIT_SUCCESS;
}

void printUsage(){
	puts("Usage: netcatunlock host port");

}
