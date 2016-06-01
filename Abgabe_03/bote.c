#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_NAME "fifo"

int main ()
{
   FILE *fd;
   char c[50];
   char text[50];


   fd = fopen(FIFO_NAME, "r");
   if (fgets(text, 50, fd) != NULL)
   {
	printf("%s", text);

   }
   /*
   read(fd, text, 50);
   printf("Die Nachricht lautet: %s\n", text); 
   */

   fclose(fd);
    
   fflush(stdout);
   return 0;
}
