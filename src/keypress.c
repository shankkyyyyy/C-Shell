#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/cget.h"

int cgets(char *buffer, int size)
{
	memset(buffer, 0, size); // Initialize buffer to zero
	
	struct termios newt,oldt; 
	// getting the current terminal settings and storing them in oldt 
	tcgetattr(STDIN_FILENO,&oldt);
	
	newt = oldt;
	// modifying the new terminal settings to disable canonical mode and echoing 
	// this will directly send the input to the program 
	// without waiting for a newline and will not display the characters typed by the user
	newt.c_lflag &= ~(ICANON | ECHO);
	// applying the new terminal settings immediately
	tcsetattr(STDIN_FILENO,TCSANOW,&newt);
	
	int j = 0;

	while(1)
	{
	
		char character = getchar();
	
		if (character == '\n' || character == '\r')
		{
			// checks for the size of the buffer to prevent overflow
			if  (j > size)
			{
				return -1;
			}
			
			if (j == 0)
			{
				strcpy(buffer,"\0");
			}
			else 
			{
				strcat (buffer, "\0");
			}
			// prints newline 
			printf("\n");
			// restores the old terminal 
			tcsetattr(STDIN_FILENO,TCSANOW,&oldt);
			// returns the buffer
			return 0;
		}

		// if the character is backspace or delete 
		else if (character == 127 || character == 8)
		{
			// if there is characters in the buffer 
			if (j > 0)
			{
				// removes the last character 
				printf("\b \b");
				// fflushes the output 
				fflush (stdout);
				// decrements the index
				j--;
			}
			// if there is no characters in the buffer
			else 
			{
				// ignores the backspace input 
				continue;
			}
		}
		// if the character is an escape character
		else if (character == '\033')
		{
			getchar(); // skip the [
			// gets the next character
			char d = getchar();
			// if it is an up arrow, it returns 10
			if (d == 'A') 
			{
				tcsetattr(STDIN_FILENO,TCSANOW,&oldt); // restore the old terminal settings before returning
				return 10; // up arrow, it returns 10 for up arrow
			}
			// if it is a down arrow, it returns 11
			if (d == 'B') 
			{
				tcsetattr(STDIN_FILENO,TCSANOW,&oldt); // restore the old terminal settings before returning
				return 11; // down arrow, it returns 11 for down arrow
			}
		}
		else 
		{
			if (j < size - 1) 
			{
				buffer[j++] = character; // add character to buffer and increment index
				printf("%c", character); // echo the character
				fflush(stdout); // flush the output to ensure it appears immediately
			}
			else 
			{
				// If buffer is full, ignore additional input
				continue;
			}
		}
	}

}

