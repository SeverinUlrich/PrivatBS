#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>


int main ()
{
   int fd;
   char *myfifo = "/tmp/myfifo";
   char buf[50];
    
   fd = open(myfifo, O_RDONLY);
   read(fd, buf, 50);
   printf("Die Nachricht lautet: %s\n", buf); 
   close(fd);
   
   return 0;
}