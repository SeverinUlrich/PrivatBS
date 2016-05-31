#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

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
    int fd;
    char *myfifo = "/tmp/myfifo";
    char text[50];
    char c[50];
    printf("Text eingeben:\n");
    
    fgets(text, 50, stdin);
    
    rot13(text, c);
    printf("%s", c);
    
    mkfifo(myfifo, 0666);
    
    fd = open(myfifo, O_WRONLY);
    write(fd, c, sizeof(c));
    printf("%i", fd);
    close(fd);
    
    unlink(myfifo);
    return 0;
}