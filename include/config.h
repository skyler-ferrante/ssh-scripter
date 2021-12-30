#ifndef CONFIG_H
#define CONFIG_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_HOST_SIZE 64

struct hnode{
	char* host;
	struct hnode* next;
};

struct hnode* new_node();

void add_node(struct hnode* tail, char* host);

struct hnode* get_hosts(char* filename);

void print_hosts(struct hnode* hosts);

#endif
