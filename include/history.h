#pragma once

char *History(FILE *fp,int times);
int AddHistory(char* command,char *filepath);
char *GetHistory(int log);
