#include<stdio.h>
#include "config.h"

int main(int argc, char** argv){
	if(argc != 2){
		printf("Usage: %s hosts\n", argv[0]);
	}
	struct hnode* hosts = get_hosts(argv[1]);

	print_hosts(hosts);
}
