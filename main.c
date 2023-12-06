#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <fcntl.h>
#define MAX_LENGTH 1024


//create new programm and execute
int executeCommand(char *args[],char *inputFile, char *outputFile){
	int inputFileFD = -1, outputFileFD = -1;
	int status;
	pid_t pid = fork();
	
	if (pid == -1){
		//fork failure
		perror("fork");
		return -1;
	}
	else if (pid == 0){
		//child process
		if (outputFile != NULL) {
            outputFileFD = open(outputFile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (outputFileFD == -1) {
				perror("open output file");
				exit(EXIT_FAILURE);
			}
            dup2(outputFileFD, STDOUT_FILENO);//stdout is remplacing by fd
            close(outputFileFD);
        }
        if (inputFile != NULL) {
            inputFileFD = open(inputFile, O_RDONLY);
            if (inputFileFD == -1) {
				perror("open input file");
				exit(EXIT_FAILURE);
			}
            dup2(inputFileFD, STDIN_FILENO);//stdin is remplacing by fd
            close(inputFileFD);
        }
		execvp(args[0], args);
		perror("execvp");
		exit(EXIT_FAILURE);
	}
	else {
		//parant process
		if (inputFile != NULL) {
			close(inputFileFD); 
    }
    if (outputFile != NULL) {
		close(outputFileFD); 
    }
		waitpid(pid, &status, 0);
		return status; //return child process's status
	}
}

int main(){
	char *outputFile = NULL;
	char *inputFile = NULL;
	char input[MAX_LENGTH];
	char *args[MAX_LENGTH];
	char *token;
	const char *delimiter = " \t\n";
	ssize_t bytes_read;
	int status = 0;
	char prompt[MAX_LENGTH];
	const char *welcom_msg = "Bienvenue dans le Shell ENSEA. \nPour quitter, tapez 'exit'. \n";
	struct timespec start, end;
    long time_elapsed;
    
    
	write(STDOUT_FILENO, welcom_msg, strlen(welcom_msg));
	write(STDOUT_FILENO, "enseash % ", 10); 
	
	while(1){
		
		outputFile = NULL;
		inputFile = NULL;
		memset(input, 0, MAX_LENGTH); //initialize input
		bytes_read = read(STDIN_FILENO, input, MAX_LENGTH-1);
		clock_gettime(CLOCK_MONOTONIC, &start); // get time before exe
		
		if (bytes_read<0){
			break;
		}
		input[bytes_read] = '\0'; //add 0 to end of list
		
		if (strcmp(input, "exit\n") == 0){
			write(STDOUT_FILENO, "Bye Bye\n ", 10); 
			break; //exit command
		}
		
		int i = 0;
		token = strtok(input, delimiter);
		while (token != NULL){
			if (strcmp(token, ">") == 0) {
				token = strtok(NULL, delimiter);  // get output file path
				outputFile = token;
			}
			else if (strcmp(token, "<") == 0) {
				token = strtok(NULL, delimiter);  // get intput file path
				inputFile = token;
			}
			else {
				args[i++] = token;  // Add normal token to argument
			}
			token = strtok(NULL, delimiter);
		}
		args[i] = NULL;
		
		status = executeCommand(args,inputFile,outputFile);
		
		clock_gettime(CLOCK_MONOTONIC, &end);//get time after exe
		time_elapsed = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000;//to calculate time on ms
		
		if (WIFEXITED(status)) { // to check if process finish
            sprintf(prompt, "enseash [exit:%d|%ldms] %% ", WEXITSTATUS(status),time_elapsed);
        } else if (WIFSIGNALED(status)) { // to check if process finish by a signal
            sprintf(prompt, "enseash [sign:%d|%ldms] %% ", WTERMSIG(status),time_elapsed);
        } else {
            sprintf(prompt, "enseash %% ");
        }
        
        write(STDOUT_FILENO, prompt, strlen(prompt));
	}
	return 0;
}
	


		
