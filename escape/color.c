#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"color.h"

void setForeground(char * color, char bold)
{
    if(strcmp(color, "black") == 0)
    {
        printf("\033[%c;30m",bold);
    }
    else if(strcmp(color, "red") == 0)
    {
        printf("\033[%c;31m",bold);
    }
    else if(strcmp(color, "green") == 0)
    {
        printf("\033[%c;32m",bold);
    }
    else if(strcmp(color, "yellow") == 0)
    {
        printf("\033[%c;33m",bold);
    }
    else if(strcmp(color, "blue") == 0)
    {
        printf("\033[%c;34m",bold);
    }
    else if(strcmp(color, "magenta") == 0)
    {
        printf("\033[%c;35m",bold);
    }
    else if(strcmp(color, "cyan") == 0)
    {
        printf("\033[%c;36m",bold);
    }
    else if(strcmp(color, "white") == 0)
    {
        printf("\033[%c;37m",bold);
    }
    else if(strcmp(color, "reset") == 0)
    {
        printf("\033[%c;39m",bold);
    }
}

void setBackground(char * color)
{
    if(strcmp(color, "black") == 0)
    {
        printf("\033[40m");
    }
    else if(strcmp(color, "red") == 0)
    {
        printf("\033[41m");
    }
    else if(strcmp(color, "green") == 0)
    {
        printf("\033[42m");
    }
    else if(strcmp(color, "yellow") == 0)
    {
        printf("\033[43m");
    }
    else if(strcmp(color, "blue") == 0)
    {
        printf("\033[44m");
    }
    else if(strcmp(color, "magenta") == 0)
    {
        printf("\033[45m");
    }
    else if(strcmp(color, "cyan") == 0)
    {
        printf("\033[46m");
    }
    else if(strcmp(color, "white") == 0)
    {
        printf("\033[47m");
    }
    else if(strcmp(color, "reset") == 0)
    {
        printf("\033[49m");
    }
}

/**
    *@brief Function printreset
    *@note  set print to default format
    *@retval void
*/
void printreset()
{
    printf("\033[0m");
}