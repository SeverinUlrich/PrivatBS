#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char *argv[])
{

	char* arg1[3];
	arg1[0]=NULL;arg1[1]=NULL;arg1[2]=NULL;
	char* arg2[3];
	arg2[0]=NULL;arg2[1]=NULL;arg2[2]=NULL;

	int i;
	int fork_pid;
	int fd[2];
	
	if(argc <= 2 || argc > 5)
	{
		printf("Fehlerhafte Parameter");
		return EXIT_FAILURE;
	}
	
	for(i = 1;i < argc; i++)
	{
		switch(i)
		{
			case 1:
				arg1[0] = argv[i];
			break;
			case 2:
				if(argv[i][0] == '-')
				{
					arg1[1] = argv[i];
					break;
				}
			case 3:
				if(arg2[0] == NULL)
				{
					arg2[0] = argv[i];
					break;
				}
			case 4:
				arg2[1] = argv[i];
				break;
		 }
	  }
	
	if( arg2[0] == NULL )
	{
		printf("Fehler bei den Parametern!");
		return EXIT_FAILURE;
	}
	if(pipe(fd) < 0)
	{
		printf("Pipe konnte nicht erstellt werden!");
		return EXIT_FAILURE;
	}
	
	if((fork_pid = fork()) < 0)
	{
		printf("Fork konnte nicht erstellt werden!");
		return EXIT_FAILURE;
	}
	else if(fork_pid > 0)
	{

		if(dup2(fd[0], 0) < 0)
		{
			printf("Oh oh, Da ging was schief beim Lesen!");
			return EXIT_FAILURE;
		}
		close(fd[1]);
		execvp(arg2[0],arg2);
	}
	else
	{

		if(dup2(fd[1], 1)<0)
		{
			printf("Da ging was anderes schief mit dem duplizieren des fds!");
			return EXIT_FAILURE;
		}
		close(fd[0]);
		execvp(arg1[0],arg1);
	}

	return EXIT_SUCCESS;
}