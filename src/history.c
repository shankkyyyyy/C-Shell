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

char *get_history(int times)
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
	
	FILE *fp = fopen(buffer,"r");
	if (fp==NULL)
	{
		perror("Error.");
		return NULL;
	}
	char temp[2000];
	char *buffer_2 = malloc(2034);
	int i = 1;
	while(fgets(temp,2000,fp)!=NULL)
	{
		i++;
		continue;
	}
	// 6 lines 2 6-2 = 3 + 1
	// 6 lines 2 6 - 2 = 4 + 1
	// i = 6
	int desired = i - times; 
	// 6 - 2 = 4
	printf("%d\n",i);
	for (int j = 0;j >= desired;j++)
	{
		fgets(temp,2000,fp);
		printf("%d: %s :desire: %d",j,temp,desired);
	}

	fgets(buffer_2,2034,fp);
	fclose(fp);
	return buffer_2;
}

int main()
{
	add_history("first\n");
	add_history("second\n");
	char *buffer = get_history(2);
	printf("%s",buffer);
	return 0;
}
