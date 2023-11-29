#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX_LENGTH 1024


//create new programm and execute
void executeCommand(char *args[]){
	pid_t pid = fork();
	if (pid == -1){
		//fork failure
		perror("fork");
	}
	else if (pid == 0){
		//child process
		if (execvp(args[0], args) == -1){
			perror("execvp");
		}
		exit(EXIT_FAILURE);
	}
	else {
		//parant process
		int status;
		waitpid(pid, &status, 0);
	}
}

int main(){
	char input[MAX_LENGTH];
	char *args[MAX_LENGTH];
	char *token;
	const char *delimiter = " \t\n";
	ssize_t bytes_read;
	
	const char *welcom_msg = "Bienvenue dans le Shell ENSEA. \nPour quitter, tapez 'exit'. \n";
	write(STDOUT_FILENO, welcom_msg, strlen(welcom_msg));
	
	while(1){
		write(STDOUT_FILENO, "ensash % ", 10); 
		memset(input, 0, MAX_LENGTH); //initialize input
		bytes_read = read(STDOUT_FILENO, input, MAX_LENGTH-1);
		if (bytes_read<0){
			break;
		}
		input[bytes_read] = '\0'; //add 0 to end of list
		if (strcmp(input, "exit\n") == 0){
			write(STDOUT_FILENO, "bye bye\n ", 10); 
			break; //exit command
		}
		int i = 0;
		token = strtok(input, delimiter);
		while (token != NULL){
			args[i++] = token;
			token = strtok(NULL, delimiter);
		}
		args[i] = NULL;
		executeCommand(args);
	}
	return 0;
}
	


		
