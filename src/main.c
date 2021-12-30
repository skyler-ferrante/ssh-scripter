#include<stdio.h>
#include "config.h"

int main(int argc, char** argv){
	struct node* hosts;
	struct node* usernames;
	struct node* passwords;
	struct node* commands;

	if(argc == 1){
		hosts = get_lines("config/hosts");
		usernames = get_lines("config/usernames");
		passwords = get_lines("config/passwords");
		commands = get_lines("config/commands");
	}
	else if(argc == 5){
		hosts = get_lines(argv[1]);
		usernames = get_lines(argv[2]);
		passwords = get_lines(argv[3]);
		commands = get_lines(argv[4]);
	}else{
		printf("Usage: %s #With config files in config/\n", argv[0]);
		printf("Usage: %s hosts_file username_file password_file commands_file", argv[0]);
		exit(-1);
	}
	
	print_lines(hosts);
	print_lines(usernames);
	print_lines(passwords);
	print_lines(commands);
}
