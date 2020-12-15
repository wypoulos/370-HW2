// coordinator.c
// Wyatt Poulos


#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	
	//Check to make sure there is a valid number of arguments
	if(argc < 3){
		printf("[Coordinator] Not enough arguments!\n");
		return 0;
	}	
	//Iterate throught the arguments starting with first dividend 
	//Argv[1] will always be the divisor 
	for(int i = 2; i < argc; i++){
		//Make uninitiallized integer value for wait value
		int turn;

		// Forking and storing the id of fork
		int id = fork();
		
		//If the fork id is 0 then we know we are int he child process
		//and should only do child process things
		if(id == 0){
			
			//Exec the chcker program passing it the correct arguments such as file, program name, 
			//divisor, dividend and null
			execlp("checker","checker",argv[1],argv[i],NULL);
		}else{
			//Because the if of fork is not 0 we know we are in the parent program
			printf("Coordinator: forked process with ID %d.\n", id);	
			printf("Coordinator: waiting for process [%d].\n", id);
			
			//Call wait so that child program has time it finish and pass it the adress of
			//turn so it can be used later to get the return value
			wait(&turn);
			
			//Call WEXITSTATUS on turn so that the return value can be gotten and put in the printf
			printf("Coordinator: child process %d returned %d.\n",id,WEXITSTATUS(turn));	
		}
	}
	//End of program!
	printf("Coordinator exiting.\n");
	return 0;
}
