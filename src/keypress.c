#include <termios.h>
#include <unistd.h>
#include <stdio.h>

int keypress()
{

	struct termios new,old;
	tcgetattr(STDIN_FILENO,&old);
	new = old;
	new.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO,TCSANOW,&new);
	while(1){
	char character = getchar();
	char strings[1024];
	if (character == '\n' || character == '\r')
	{
		printf("\n");
		continue;

		
	}
	if (character == '\033')

	{
		getchar();
		char d = getchar();
		if (d == 'A') printf("Pressed Up arrow.\n");
		if (d == 'B') printf("Pressed Down arrow.\n");
		fflush(stdout);
		tcsetattr(STDIN_FILENO,TCSANOW,&new);
		continue;
	}
	if (character == 127 || character == 8)
	{
		printf("\b \b");
		fflush(stdout);
		continue;
	}	

	else 
	{
		
		printf("%c",character);
		tcsetattr(STDIN_FILENO,TCSANOW,&new);
		continue;
	}
	}
}

int main()
{
	keypress();
}
