#include <stdio.h>
#include <sys/types.h>
#include <unistd.h> 
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>


// main function 
int main()
{	
	// loop for shell [cannot end]
	while (1){
	// declaring a pid_t variable 
	pid_t pid = fork();

	// statement for checking fork succeed or not.
	if (pid == -1)
	{
		// prinint error
		perror("Fork Cannot Be done.\n");
		return 1;

	}
	// if fork has worked and the pid var equal to zero then continue with the shell executation.
	else if (pid == 0)
	{
		printf("Shell?> ");
		// input variable declaration
		char input[150]; 
		// taking input
		fgets(input,150,stdin);
		// taking the length of the input
		size_t len = strlen(input);
		// making the last byte 0
		input[len - 1] = '\0';	
		// tokenizing the input string; delim is " "
		char *output = strtok(input," ");
		// count for args
		int i = 0;
		// dynamically allocating memory for string array/double pointer
		char **args = malloc(1500);
		// making the first output into args[0]
		args[i] = output;
		
		// statement if first argument is change directory; 
		if (strcmp(args[i],"cd")==0)
		{
			// gets the directory name
			output = strtok(NULL, " ");
			// changes to that directory
			chdir(output);
			// free's the dynamically allocated array
			free(args);
			// continues the loop;
			continue;
		}
	
		// increments the count.	
		i++;
		// while loop for making sure output doesnt end up NULL
		while (output != NULL)
		{
			// tokenizing string
			output = strtok(NULL," ");
			// statement for if output == NULL
			if (output == NULL)
			{
				// increments the count; cause need to add NULL atlast for the dynamic array;
				i++;
				// breaking from the while loop;
				break;
			}
			// writing to the dynamic array 
			args[i] = output;
			// printing it to the screen
			printf("%d: %s \n",i,output);
			// increments
			i++;
		}	
		// make sure the last dynamic array should NULL
		args[i] = NULL;
	
		// if execvp returns that means the function has failed.
		int result = execvp(args[0],args);
		if (result)
		{
			// giving the user a error message
			perror("Cannot Find the Command.\n");
			
			// freeing the given dynamic array.
			free(args);
			// and continuing the loop.
			continue;	
		}
		// freeing the args
		free(args);
	
	}
	else 
	{	// declaring the variable statis for the function waitpid();
		int status;
		// waiting for the child to finish .
		waitpid(pid,&status,0);
	}

}
}
