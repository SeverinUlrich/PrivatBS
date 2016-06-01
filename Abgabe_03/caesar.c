#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <ctype.h>


#define FIFO_NAME "fifo"
void rot13(char a[],  char b[]){
    
        int i = 0, lo = 65, hi = 90, diff = 32, rot = 13;
        while(a[i] != '\0'){
                /*uppercase*/
                if(a[i] > lo-1 && a[i] < hi+1){
                        if(a[i]-lo < rot)
                                b[i] = a[i] + rot;
                        else
                                b[i] = a[i] - rot;
                }
                /*lowercase*/
                else if (a[i] > lo+diff-1 && a[i] < hi+diff+1){
                        if(a[i]-(lo+diff) < rot )
                                b[i] = a[i] + rot;
                        else
                                b[i] = a[i] - rot;
                }
                /*no alpha*/
                else
                        b[i] = a[i];
                i++;
        }
        b[i] = '\0';
return;
}

int main (int agrc, char *argv[])
{
             
   /* char *fifo = "fifo"; */
    char text[50];
    char c[50];
    printf("Text eingeben:\n");
    
    fgets(text, 50, stdin);
    
    mkfifo(FIFO_NAME, 0777);  
    
    rot13(text, c);
    printf("%s", c);
    
    FILE *fd = fopen(FIFO_NAME, "w");
    printf("test");
    fprintf(fd, "%s", c);
	fflush(fd);
    fclose(fd);

    unlink(FIFO_NAME);
    return EXIT_SUCCESS;
}
