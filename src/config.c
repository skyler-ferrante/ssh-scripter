#include "config.h"

struct node* new_node(){
	return (struct node*) malloc(sizeof(struct node));
}

void add_node(struct node* tail, char* line){
	tail->line = strdup(line);
	tail->next = NULL;
}

struct node* get_lines(char* filename){
	FILE* file;

	//If given file is readable
	if( (file = fopen(filename, "r")) ){
		char line[MAX_LINE_SIZE];

		struct node* head = new_node();
		struct node* tail = head;
		
		if( fscanf(file, "%s\n", line) != 1){
			fprintf(stderr, "Cannot read first line from %s\n", filename);
			exit(-1);
		}
		
		add_node(tail, line);
	
		//While able to read line
		while( fscanf(file, "%s\n", line) != EOF ){
			tail->next = new_node();
			tail = tail->next;
			add_node(tail, line);
		}

		return head;
	}
	exit(-1);
}

void print_lines(struct node* list){
	for(struct node* curr = list; curr; curr = curr->next){
		printf("%s\n", curr->line);
	}
}
