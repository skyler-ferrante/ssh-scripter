#include<stdio.h>
#include "config.h"
#include "ssh_run.h"

//#define LOG_LEVEL SSH_LOG_PROTOCOL
#define LOG_LEVEL SSH_LOG_NOLOG

int main(int argc, char** argv){
	ssh_session my_ssh_session = ssh_new();
	long timeout = 4;

	struct node *hosts, *usernames, *passwords, *commands;

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

	struct node *u, *h, *p, *c;

	for(h = hosts; h; h = h->next){
		char* username, *password, *host = h->line;
		
		session_init(my_ssh_session, host, 22, LOG_LEVEL, timeout); 
		connect_session(my_ssh_session, host);

		int rc = SSH_AUTH_ERROR;

		for(u = usernames; u; u = u->next){
			for(p = passwords; p; p = p->next){
				username = u->line;
				password = p->line;

				printf("Trying: %s,%s,%s\n", host, username, password);				
				rc = ssh_userauth_password(my_ssh_session, username, password);		

				if( rc == SSH_AUTH_SUCCESS )
					break;
				
				if( rc == SSH_AUTH_AGAIN ){
					printf("Too many attempts\n");
					break;
				}
			}

			if( rc == SSH_AUTH_SUCCESS || rc == SSH_AUTH_AGAIN )
				break;
		}

		if( rc == SSH_AUTH_AGAIN )
			continue;
		
		printf("SUCCESS: %s,%s,%s\n", host, username, password);
		
		ssh_channel my_channel;

		printf("HERE\n");
		
		char buffer[BUFFER_SIZE];
		buffer[BUFFER_SIZE-1] = '\0';
		int nbytes;
		char* command;

		for(c = commands; c; c = c->next){
			create_channel(my_ssh_session, &my_channel);
			
			command = c->line;
			printf("Command:%s:\n", command);

			int rc = ssh_channel_request_exec(my_channel, command);
			if( rc != SSH_OK ){
				ssh_channel_close(my_channel);
				ssh_channel_free(my_channel);
				cleanup(my_ssh_session);
				printf("Channel failed with rc %d\n", rc);
			}
			
			while( (nbytes = ssh_channel_read(my_channel, buffer, sizeof(buffer), 0)) ){
					if ( fwrite(buffer, 1, nbytes, stdout) != nbytes){
						ssh_channel_close(my_channel);
						ssh_channel_free(my_channel);
						break;
					}
			}

			ssh_channel_send_eof(my_channel);
			ssh_channel_close(my_channel);
			ssh_channel_free(my_channel);
		}
	}

	cleanup(my_ssh_session);
	//print_lines(hosts);
	//print_lines(usernames);
	//print_lines(passwords);
	//print_lines(commands);
}
