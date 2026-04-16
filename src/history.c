#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "../include/history.h"

// define's
#define BufferSize 1024

// functions 
char *History(FILE *fp,int times)
{
	int i = 1;
	char tempbuffer[1024];
	while (times > i && fgets(tempbuffer,BufferSize,fp)!=NULL)
	{
		i++;
		continue;
	}
	char *buffer = malloc(BufferSize);
	if(fgets(buffer,BufferSize,fp)== NULL) return NULL;
	return buffer;
}

int AddHistory(char *command,char *filepath)
{
	FILE *fp = fopen(".temp.txt","w+");
	if (fp == NULL)
	{
		perror("error opening the temp file. \n");
		return -1;
	}
	
	fprintf(fp,"%s\n",command);
	
	FILE *fp_history = fopen(filepath,"a+");
	if (fp_history == NULL)
	{
		fclose(fp);
		perror("error opening the history file.\n");
		return -1;
	}
	
	char buffer[BufferSize];
	
	while(fgets(buffer,BufferSize,fp_history)!=NULL)
	{
	    if(fprintf(fp,"%s",buffer) < 0) return -1;
	}
	
	fclose(fp);
	fclose(fp_history);
	
	remove(filepath);
	if(rename(".temp.txt",filepath) != 0) return -1;
	return 0;
}

char *GetHistory(int log)
{
	FILE *fp = fopen("h.txt","a+");
	if (fp == NULL)
	{
		perror(" ");
		return NULL;
	}
	
	char *OutputBuffer = History(fp,4);
	printf("%s\n",OutputBuffer); // must free the buffer;
}

int main()
{
	GetHistory(1);
}
