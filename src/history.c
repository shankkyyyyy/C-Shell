#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/history.h"

// define's
#define BufferSize 1024

// functions 
char *History(FILE *fp,FILE *fp2,int times)
{

	char TemBuffer[BufferSize];
	int CountOfLines = 0;
	
	while(fgets(TemBuffer,BufferSize,fp2)!=NULL)
	{
		CountOfLines++;
		continue;
	}
	fclose(fp2);

	int NumberOfLines = CountOfLines - times;
	
	// count
	int i = 0;
	
	memset(TemBuffer,0,BufferSize);
	
	while(i!=NumberOfLines)
	{
		fgets(TemBuffer,BufferSize,fp);
		//count
		i++;
	}
	// last read.
	
	char *buffer = malloc(BufferSize);
	fgets(buffer,BufferSize,fp);
	//closing the file pointer;
	fclose(fp);
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

int add_history(char* command)
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
	
	if (fprintf(fp,"%s\n",command)< 0)
	{
		perror("Error Writing To File.\n");
		return 1;
	}
	
	fclose(fp);
	return 0;
}

char *GetHistory(int log)
{
	FILE *fp = fopen("/home/gigu/.history_C-Shell.txt","a+");
	FILE *fp2 = fopen("/home/gigu/.history_C-Shell.txt","a+");
	char *OutputBuffer = History(fp,fp2,4);
	return OutputBuffer; // must free the buffer;
}

int main()
{
	AddHistory("ls","h.txt");
	AddHistory("cd","h.txt");
	AddHistory("clear","h.txt");
}
