#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include "../include/cget.h"


// main function
int main()
{
    
    // loop for shell [cannot end]
    while (1) {
	
        printf("Shell?> ");
        // input variable declaration
        char *buffer = malloc(1024);
        // taking input
        cgets(buffer, 1024);
        // taking the length of the input
        size_t len = strlen(buffer);
       
        // making the last byte 0
		if (len==0)
		{
			continue;
		}
		
        // tokenizing the input string; delim is " "
        char *output = strtok(buffer, " ");
        // count for args
        int i = 0;
        // dynamically allocating memory for string array/double pointer
        char **args = malloc(1500);
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
            // free's the dynamically allocated array
            free(args);
            // continues the loop;
            continue;
        }
        
        // increments the count.
        i++;
        // while loop for making sure output doesnt end up NULL
        while (output != NULL) {
            // tokenizing string
            output = strtok(NULL, " ");
            // statement for if output == NULL
            if (output == NULL) {
                // increments the count; cause need to add NULL atlast for the dynamic array;
                i++;
                // breaking from the while loop;
                break;
            }
            // writing to the dynamic array
            args[i] = output;
            // printing it to the screen
            
            // increments
            i++;
        }
        // make sure the last dynamic array should NULL
        args[i] = NULL;
    

    
    // declaring a pid_t variable
    pid_t pid = fork();
    
    // statement for checking fork succeed or not.
    if (pid == -1) {
        // prinint error
        perror("Fork Cannot Be done.\n");
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
    }
}

}
