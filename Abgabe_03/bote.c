#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main ()
{
   int fd;
   char *myfifo = "fifo";
   char text[50];


   fd = open(fifo, O_RDONLY);
   read(fd, text, 50);
   printf("Die Nachricht lautet: %s\n", text); 
   close(fd);
    
   return 0;
}