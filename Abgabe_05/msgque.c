#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>


struct mail {
	long int mtype;
	char mtext[140];
};

int readMessageQueue(int id,struct mail *receive,int from);

int sender(int id);

int receiver(int id);

int main(int argc, char const *argv[]);

int sender(int id)
{
	int queue = msgget(id,IPC_CREAT | 0660);
	if(queue == -1)
	{
		fprintf(stderr, "Mail-ID nicht vorhanden \n");
		return EXIT_FAILURE;
	}
	struct mail send;
	do
	{
		printf("Bitte geben Sie die Prioritaet der Nachricht ein:( 1 - 20 ) \n");
		scanf("%ld",&(send.mtype));
		getchar();
	}while(send.mtype < 1 || send.mtype > 20);

	printf("Geben Sie Ihre Nachricht ein:\n");
	scanf("%[^\n]",send.mtext);
	getchar();

	if(msgsnd (queue,&send,sizeof(struct mail),0)  == -1)
	{
		fprintf(stderr, "Die Nachricht konnte nicht gesendet werden \n");
		printf(": %s\n", strerror( errno ));
		return EXIT_FAILURE;
	}
	printf("Nachricht gesendet \n");
	return EXIT_SUCCESS;
}

int receiver(int id)
{
	int queue = msgget(id,IPC_CREAT | 0660);
	if(queue == -1)
	{
		fprintf(stderr, "Mail-ID nicht vorhanden \n");
		return EXIT_FAILURE;
	}
	struct mail receive;
	int menu;
	do
	{
		printf("Bitte auswaehlen: \n 1. Sehr Wichtig\n 2. Wichtig\n 3. Normal\n 4. Beenden \n");
		scanf("%d",&menu);
		getchar();
		switch(menu)
		{
			case 1:
				menu = readMessageQueue(queue,&receive,-5);
				break;
			case 2:
				menu = readMessageQueue(queue,&receive,-9);
				break;
			case 3:
				menu = readMessageQueue(queue,&receive,-20);
				break;
		}
		if(menu == -5)
		{
			msgctl(queue, IPC_RMID, NULL);
			fprintf(stderr, "Das Postfach ist leer oder die Nachricht konnte nicht empfangen werden \n");
			return EXIT_FAILURE;
		}
	}while(menu > 0 && menu < 4);

	return EXIT_SUCCESS;
}

int readMessageQueue(int id,struct mail *receive,int from)
{
	if(msgrcv(id,receive,sizeof(struct mail),0,from) == -1)
	{
		if(errno != 0)
		{
			return -5;
		}
		return 0;
	}
	printf("Nachricht :\n%s\n", (*receive).mtext);
	return 1;
}

int main(int argc, char const *argv[])
{
	if(argc != 3)
	{
		fprintf(stderr, "Bitte geben Sie den Aufruf richtig ein (./a.out s|r id) \n");
		return EXIT_FAILURE;
	}

	int id = strtol(argv[2],NULL,10);
	if(id == 0)
	{
		fprintf(stderr, "Mail-ID nicht vorhanden \n");
		return EXIT_FAILURE;
	}
	if(argv[1][0]=='s')
	{
		return sender(id);
	}
	else
	{
		return receiver(id);
	}
}