#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include "../include/cget.h"
#include "../include/history.h"

extern int GB_log = 0;

// main function
int main()
{
    
    // loop for shell [cannot end]
    while (1) {
	
        printf("Shell?> ");
        // input variable declaration
        char *buffer = malloc(1024);

        memset(buffer,0,1024);
        // taking input
        int identifier = cgets(buffer,1024,GB_log);


        // making the GB_log zero for getting the history once more; 
        if (GB_log > 0)
        {
            GB_log = 0;
        }

        // taking the length of the input
        size_t len = strlen(buffer);
       
        // making the last byte 0
		if (len==0)
		{
			free(buffer);
			continue;
		}
		
        // tokenizing the input string; delim is " "
        char *output = strtok(buffer, " ");
        if (output == NULL)
        {
            printf("NULL FOUND......"); 
            return -1;
        }

        // count for args
        int i = 0;
        // dynamically allocating memory for string array/double pointer
        char **args = malloc(64 * sizeof(char *));
        if (args == NULL)
        {
            perror("Cannot allocate memory to args");
            return 1;
        }
        // making the first output into args[0]
        args[i] = output;
        
        // statement if first argument is change directory;
        if (strcmp(args[i], "cd") == 0) {
            // gets the directory name
            output = strtok(NULL, " ");
            // changes to that directory
            if (chdir(output)== -1)
            {
                perror("Cannot Change Directory.\n");
            }
            
            // continues the loop;
            continue;
        }
        
        while (output != NULL) {
            output = strtok(NULL, " ");
            i++;
            args[i] = output;
    
    // declaring a pid_t variable
    pid_t pid = fork();
    
    // statement for checking fork succeed or not.
    if (pid == -1) {
        // prinint error
        perror("Fork Cannot Be done.\n");
        free(args);
        return 1;
    }
    // statement for child process
    else if (pid == 0) {
        int result = execvp(args[0], args);
        if (result) {
            // giving the user a error message
            perror("Cannot Find the Command.\n");
            
            // freeing the given dynamic array.
            free(args);
            // and continuing the loop.
            exit(1);
        }
        // freeing the args
        free(args);
    }
    else {
        // declaring the variable statis for the function waitpid();
        int status;
        // waiting for the child to finish .
        waitpid(pid, &status, 0);
        // free the dynamically allocated args
        free(args);
    }
}

}
}
