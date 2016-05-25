#include <stdio.h>
#include <unistd.h>

extern char **environ;
char uvar[];

int main (int argc, char *argv[])
{
    
setenv("BSPRAKTIKUM", "ISTSUPER", 0);

int i =0;
while(environ[i] != NULL)
    {
        printf("%s\n", environ[i++]);
    }    

printf("Bitte geben Sie eine Umgebungsvariable ein:\n");
scanf("%s", &uvar);
char *wert;


printf("%s", getenv(uvar));


int j = 0;

while (environ[j] != NULL)
    {
    if(strcmp(uvar, getenv(uvar)) == 0)
        {
        printf("%s -> %s", uvar, getenv(wert));
        return 0;
        }
    else
        {
        j++;
        }
    }
   
}