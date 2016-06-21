#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>

#define SERVER_PORT 4003

typedef enum {false, true} bool;


int main (){
    int sd;
    struct sockaddr_in sin;
    int sin_len = sizeof(sin);
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(SERVER_PORT);

    sd = socket(AF_INET, SOCK_STREAM, 0);
    bind(sd, (struct sockaddr *)& sin, sizeof(sin));
    listen(sd, 5);

    com(sd, sin, &sin_len);

    unlink((const char *)& sin);
    return EXIT_SUCCESS;

}


int com(int sd, struct sockaddr_in sin, int *sin_len){
    int n_sd;
    char stichwort[50];

    FILE *sockstream;
    char *wel = "Willkommen \n";
    char *bye = "Wiedersehen \n";
    while(true){

        n_sd = accept(sd, (struct sockaddr*) &sin, (unsigned long*)&sin_len);
        sockstream = fdopen(n_sd, "r+");
        fprintf(sockstream, "%s\n", wel);
        rewind(sockstream);
        while(true){
            fprintf(sockstream, "%s\n", "Bitte Stichwort eingeben: \n");
            rewind(sockstream);
            fscanf(sockstream, "%s", &stichwort);
            rewind(sockstream);
            if(strcmp(stichwort, "EXIT") == 0){
                break;
            }
            Stichwortsuche(sockstream, stichwort);
        }
        close(n_sd);
    }
    return EXIT_SUCCESS;
}

int Stichwortsuche(FILE *sockstream, char stichwort[]){
    if(strcmp("Hallo", stichwort) == 0){
        fprintf(sockstream, "%s\n", "Welt");
    }
    else if(strcmp("Test", stichwort) == 0){
        fprintf(sockstream, "%s\n", "123");
    }
    else if(strcmp("blabla", stichwort) == 0){
        fprintf(sockstream, "%s\n", "blubb");
    }
    else if(strcmp("BS", stichwort) == 0){
        fprintf(sockstream, "%s\n", "Praktikum");
    }
    else if(strcmp("TH", stichwort) == 0){
        fprintf(sockstream, "%s\n", "Koeln");
    }    
    else{
        fprintf(sockstream, "%s\n", "Wort nicht gefunden!");
    }
    rewind(sockstream);
    return EXIT_SUCCESS;
}
