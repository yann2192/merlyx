#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "creseau.h"

char * substr(char * input, int start, int end)
{
  int count = (end-start + 1);
  char * s = calloc(count, sizeof(char));
  int i = 0;
  for( ; i < count ; ++i)
    s[i] = input[i + start];
  s[count - 1] = '\0';
  return s;
}

/**
 * Permet de recuperer le nom des interfaces et le MTU.
 */
void interface()
{
  FILE * file = NULL;
  int i, start, end;
  char * interfacename;
  char * mtu;
  char buffer[1024];

  system("netstat -i > file.temp");
  
  file = fopen("file.temp", "r");
  if(file != NULL){
    for(i = 0 ; i < 2 ; ++i)
      fgets(buffer, 1024, file);
    do{
      fgets(buffer, 1024, file);
      if(feof(file))
	break;
      /* Recuperation du nom de l'interface. */
      start = 0;
      for(i = 0 ; i < 1024 && !isspace(buffer[i]) ; i++);
      end = i;
      interfacename = substr(buffer, start, end);
      
      for( ; i < 1024 && isspace(buffer[i]) ; ++i);
      start = i;

      /* Recuperation du mtu. */
      for( ; i < 1024 && !isspace(buffer[i]) ; i++);
      end = i;
      mtu = substr(buffer, start, end);
      
      printf("Interface detecte : \n\tname = %s\n\tmtu = %s\n", interfacename, mtu);
      free(interfacename);
      free(mtu);

    }while(!feof(file));
    fclose(file);
  }
}
