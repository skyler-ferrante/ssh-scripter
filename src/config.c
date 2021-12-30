#include "config.h"

struct hnode* new_node(){
	return (struct hnode*) malloc(sizeof(struct hnode));
}

void add_node(struct hnode* tail, char* host){
	tail->host = strdup(host);
	tail->next = NULL;
}

struct hnode* get_hosts(char* filename){
	FILE* file;

	//If given file is readable
	if( (file = fopen(filename, "r")) ){
		char host[MAX_HOST_SIZE];

		struct hnode* head = new_node();
		struct hnode* tail = head;
		
		if( fscanf(file, "%s\n", host) != 1){
			fprintf(stderr, "Cannot read host from %s\n", filename);
			exit(-1);
		}
		
		add_node(tail, host);
	
		//While able to read host	
		while( fscanf(file, "%s\n", host) != EOF ){
			tail->next = new_node();
			tail = tail->next;
			add_node(tail, host);
		}

		return head;
	}
	exit(-1);
}

void print_hosts(struct hnode* hosts){
	for(; hosts; hosts = hosts->next){
		printf("%s\n", hosts->host);
	}
}
