#include <stdio.h>
#include <stdlib.h>

int add_history(const char* command)
{

	char buffer[1024];
	char *home = getenv("HOME");

	if (home == NULL)
	{
		perror("Cannot Find the Home Directory");
		return 1;
	}
	if (snprintf(buffer,1024,"%s/.history_C-Shell.txt",home) < 0)
	{
		return 1;
	}
	
	FILE *fp = fopen(buffer,"a+");
	
	if (fp == NULL)
	{
		perror("Cannot Open The File For History.");
		return 1;
	}
	
	int result = fprintf(fp,command);
	if (result < 0)
	{
		fclose(fp);
		perror("Cannot Write To History File.");
		return 1;
	}
	fclose(fp);
	return 0;
}

int main()
{
	add_history("first\n");
	add_history("second\n");
	return 0;
}
