#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

#define FUSS_B 15.51337
#define FUSS_A 13.13123
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

	int sem_id,sem_check;
	unsigned short marker[1];	
	sem_id = semget (IPC_PRIVATE, 1, IPC_CREAT|0666);
	if(sem_id == -1) 
	{
		fprintf(stderr,"Fehler beim Semaphore (1)!\n");
		return EXIT_FAILURE;
	}
	marker[0] = 1;
	sem_check=semctl(sem_id, 1, SETALL, marker);
	if(sem_check < 0)
	{
		fprintf(stderr,"Fehler beim Semaphore (2)!\n");
		return EXIT_FAILURE;
	}

	int pid[2];
	int *sperr_fuer_kind,id_sperr,id;
	id_sperr = shmget( IPC_PRIVATE, sizeof(int),0600);
	if(id_sperr == -1)
	{
		fprintf(stderr, "Shared Memory konnte nicht erstellt werden weil -1!");
		return EXIT_FAILURE;
	}
	sperr_fuer_kind = (int*)shmat(id_sperr,0,0);
	if(sperr_fuer_kind == NULL)
	{
		fprintf(stderr, "Shared Memory konnte nicht erstellt werden weil eingebundener Speicher = NULL!	");
		return EXIT_FAILURE;
	}

	double *area;
	id = shmget( IPC_PRIVATE, sizeof(double),0600);
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


	/* Semaphore Strukturen zum sperren und freigeben*/
	struct sembuf enter, leave;
	enter.sem_num = 0;	/* Semaphor 0 in der Gruppe*/
	enter.sem_op = -1;	/* blockieren*/
	enter.sem_flg = SEM_UNDO;
	leave.sem_num = 0;	/* Semaphor 0 in der Gruppe*/
	leave.sem_op = 1;	/* freigeben*/
	leave.sem_flg = SEM_UNDO;
	/* Bereich zuruecksetzen*/


	*area = ((FUSS_B+FUSS_A)*17);
	*sperr_fuer_kind = 0;

	pid[0] = fork();
	if(pid[0] == -1)
	{
		fprintf(stderr, "Fork konnte Kindprozess 1 nicht erzeugen!");
		return EXIT_FAILURE;
	}
	if(pid[0] == 0)	
	{
		while(1)
		{

			if( semop(sem_id,&enter,1) < 0)
			{
				fprintf(stderr,"Fehler bei Semaphore (3)!\n");
				return EXIT_FAILURE;
			}
			if(*sperr_fuer_kind == 1 && *area > 0){

				if( semop(sem_id,&leave,1) < 0)
				{
					fprintf(stderr,"Fehler bei Semaphore (4)!\n");
					return EXIT_FAILURE;
				}
				continue;
			}
			if(*area > 0)
			{
				*area -= FUSS_A;
			}else{break;}
			*sperr_fuer_kind = 1;

			if( semop(sem_id,&leave,1) < 0)
			{
				fprintf(stderr,"Fehler bei Semaphore (5)!\n");
				return EXIT_FAILURE;
			}
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
			while(1)
			{
				if( semop(sem_id,&enter,1) < 0)
				{
					fprintf(stderr,"Fehler bei Semaphore (6)!\n");
					return EXIT_FAILURE;
				}
				if(*sperr_fuer_kind == 2 && *area > 0){
					if( semop(sem_id,&leave,1) < 0)
					{
						fprintf(stderr,"Fehler bei Semaphore (7)!\n");
						return EXIT_FAILURE;
					}
					continue;
				}
				if(*area > 0)
				{
					*area -= FUSS_B;
				}else{break;}
				*sperr_fuer_kind = 2;
				if( semop(sem_id,&leave,1) < 0)
				{
					fprintf(stderr,"Fehler bei Semaphore (8)!\n");
					return EXIT_FAILURE;
				}
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
	semctl(sem_id, 0, IPC_RMID);

	if(*area < 0.1 && *area > -0.1)
	{
		shmdt(area);
		shmdt(sperr_fuer_kind);
		shmctl(id, IPC_RMID, 0);
		shmctl(id_sperr, IPC_RMID, 0);
		printf("Gut\n");
		return EXIT_SUCCESS;
	}
	else
	{
		shmdt(area);
		shmdt(sperr_fuer_kind);
		shmctl(id, IPC_RMID, 0);
		shmctl(id_sperr, IPC_RMID, 0);
		printf("Nicht so gut\n");
		return EXIT_FAILURE;
	}
}