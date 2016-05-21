#include <stdio.h>
#include <string.h>

int main (int argc, char *argv[]){
  int i=0;
  long int erg;
  char operand;
    
    erg = strtol(argv[1],argv,10);
    
 for (i=1; i<argc; i++)
 {
   			if(i % 2 == 1 && i > 2)
			    {
				    switch(operand){
					    case '+':
						    erg += strtol(argv[i],argv,10);
					    break;
					    case '-':
						    erg -= strtol(argv[i],argv,10);
					    break;
					    case 'x':
						    erg *= strtol(argv[i],argv,10);
					    break;
					    case '/':
						    erg /= strtol(argv[i],argv,10);
					    break;
   
          }
       }
       else
       {
         operand = argv[i][0];
       }
     }
   
   
   printf("Das Ergebnis ist: %i", erg);
   
}