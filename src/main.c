#include<stdio.h>
#include "config.h"

int main(int argc, char** argv){
	if(argc != 5){
		printf("Usage: %s host-file command-file\n", argv[0]);
		exit(-1);
	}

	struct node* hosts = get_lines(argv[1]);
	struct node* usernames = get_lines(argv[2]);
	struct node* passwords = get_lines(argv[3]);
	struct node* commands = get_lines(argv[4]);
	
	print_lines(hosts);
	print_lines(usernames);
	print_lines(passwords);
	print_lines(commands);
}
