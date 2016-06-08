#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define FUSS_B 15.3
#define FUSS_A 13.7
#define SEG_SIZE sizeof(double)

int main(int argc, char * argv[])
{
	int i, sleep_time;
	if(argc <= 1)
	{
		fprintf(stderr,"Geben Sie eine Zeit in Mikrosekunden an!\n");
		return EXIT_FAILURE;
	}
	sleep_time = strtol(argv[1],NULL,10);
	int pid[2];
	double *area, id;
	id = shmget( IPC_PRIVATE, SEG_SIZE,0600);
	if(id == -1)
	{
		fprintf(stderr, "Shared Memory konnte nicht erstellt werden weil ID = -1!");
		return EXIT_FAILURE;
	}
	area = (double*)shmat(id,0,0);
	if(area == NULL)
	{
		fprintf(stderr, "Shared Memory konnte nicht erstellt werden weil eingebundener Speicher = NULL!	");
		return EXIT_FAILURE;
	}
	*area = ((FUSS_B+FUSS_A)*17);

	pid[0] = fork();
	if(pid[0] == -1)
	{
		fprintf(stderr, "Fork konnte Kindprozess 1 nicht erzeugen!");
		return EXIT_FAILURE;
	}
	if(pid[0] == 0)
	{
		while(*area > 0)
		{
			*area -= FUSS_A;
			printf("POTT - %lf\n",*area);
			fflush(stdout);
			usleep(sleep_time);
		}
		return EXIT_SUCCESS;
	}
	else
	{	
		pid[1] = fork();
		if(pid[1] == -1)
		{
			fprintf(stderr, "Fork konnte Kindprozess 2 nicht erstellen!");
			return EXIT_FAILURE;
		}
		if(pid[1] == 0)
		{
			while(*area > 0)
			{
				*area -= FUSS_B;
				printf("PISS - %lf\n",*area);
				fflush(stdout);
				usleep(sleep_time);
			}
			return EXIT_SUCCESS;
		}
		for(i=0;i<2;i++)
		{
			waitpid(*(pid+i),NULL,0);
		}
	}

	if(*area < 0.1 && *area > -0.1)
	{

		shmdt(area);
		shmctl(id, IPC_RMID, 0);
		printf("Gut\n");
		return EXIT_SUCCESS;
	}
	else
	{

		shmdt(area);
		shmctl(id, IPC_RMID, 0);
		printf("Nicht so gut\n");
		return EXIT_FAILURE;
	}
}