#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

int main()
{
int i;
int pid[3];
for(i=0; i<3;i++)
{
    pid[i] = fork();
    if (pid[i] == 0)
    {
        int c;
        for(c=0;c<20; c++)
        {
            printf("%i", i);
            fflush (stdout);
            usleep(1);
        }
        exit(0);
    }
    else
    {
        
    }
}
for (i=0;i<3;i++)
{
    waitpid(pid[i], NULL, 0);
}
printf("\n");
return 0;
}