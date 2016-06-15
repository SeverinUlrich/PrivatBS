#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>


char* formatRights(int st_mode);


void analyse(const char * filepath)
{
	struct stat fileinfo;
	if(stat(filepath, &fileinfo) == -1)
	{
		fprintf(stderr,"Laden der Informationen fehlgeschlagen! \n");
		return;
	}
	printf("Datei\t\t\t: %s\n",filepath);
	printf("Dateigroesse\t\t: %d Bytes\n",fileinfo.st_size);
	printf("Besitzer\t\t: %d\n",fileinfo.st_uid);
	printf("Inode Nummer\t\t: %d\n",fileinfo.st_ino);
	printf("letzter Zugriff\t\t: %s",ctime(&(fileinfo.st_atime)));
	printf("letzte Aenderung\t: %s",ctime(&(fileinfo.st_mtime)));
	printf("letzte Inode Aenderung\t: %s",ctime(&(fileinfo.st_ctime)));
	printf("Zugriffsrechte\t\t: %s\n",formatRights(fileinfo.st_mode));
	printf("\n");
}

char* formatRights(int st_mode)
{
	int i;
	char* l_rwx = (char*)malloc(sizeof(char)*10);
	if(l_rwx == NULL)
	{
		return (char*)NULL;
	}
	const char rwx[] = "rwxrwxrwx";
	int bits[] = {
		S_IRUSR,S_IWUSR,S_IXUSR,
		S_IRGRP,S_IWGRP,S_IXGRP,
		S_IROTH,S_IWOTH,S_IXOTH
	};
	for(i = 0; i < 9; i++) {

		if(st_mode & bits[i])
			l_rwx[i]=rwx[i];
		else
			l_rwx[i] = '-';
	}
	l_rwx[9]='\0';
	return l_rwx;
}

int main(int argc, char* argv[])
{

	if(argc <= 1)
	{
		fprintf(stderr,"Bitte richtig aufrufen ./a.out <Datei>");
		return EXIT_SUCCESS;
	}

	int i = 1;
	while(argv[i] != NULL)
	{
		analyse(argv[i]);
		i++;
	}
	return EXIT_SUCCESS;
}