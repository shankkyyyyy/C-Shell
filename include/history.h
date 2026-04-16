#pragma once

char *History(FILE *fp,FILE *fp2,int times);
int add_history(char* command);
char *GetHistory(int log);
