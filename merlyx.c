#include "cpuinfo.h"
#include "creseau.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, const char *argv[])
{
  int ok = 0;
  char choix[50];

  while( !ok )
    {
      printf("\n\n\n\n");
      printf("Information sur le CPU (1). \n");
      printf("Information sur la carte (2). \n");
      printf("Quitter (3).\n\n\n\n\n");
 
      fgets(choix, 50, stdin);
      system("clear");

      if( choix[0] == '1' )
	{
	  CPUID_INFO info = CPUID_INFO_create();
	  CPUID_INFO_fprintf(stdout, info);
	  CPUID_INFO_free(info);
	}

      else if( choix[0] == '2' )
	{
	  interface();
	}

      else if( choix[0] == '3' )
	{
	  ok = 1;
	}

    }
    return 0;
}
