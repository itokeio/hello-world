#include<stdio.h>
#include<stdlib.h>

#define OK 0
#define OVER 2
#define FATAL 1

//读取字符串的函数
int read_line(char place[] , int n)
{
    int ch=0,i=0;
    while((ch=getchar())!='\n')
    {
        if(i<n) place[i++] = ch;
    }
    place[i] = '\0';
    return i;
}

//输出字符串的函数
int print_line(char * place,int n)
{
    for(int i=0 ; place[i]!='\0' ; i++)
    {
        printf("%c",place[i]);
    }
    return OK;
}



