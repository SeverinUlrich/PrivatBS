#include <stdio.h>
#include <stdlib.h>

int main()
{
int i;
int j;
int k;
pid = fork();

if(pid ==0)
{
    for (i=0;i<20;i++)
    {
        printf("1");
        usleep(1);
    }
    exit(1);
}
else if (pid>0)
{
    pid = fork();
    if (pid ==0)
    {
        for(j=0;j<20;j++)
        {
            printf("2");
            usleep(1);
        }
        exit(2);
    }    
    else if (pid > 0)
    {
        pid = fork();
        
        if (pid ==0)
        {
            for (k=0;k<20;k++)
            {
                printf("3")
                usleep(1);
            }
            exit(3)
        }
        
    }
}
}