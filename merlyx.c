#include "cpuinfo.h"
#include "creseau.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void usage()
{
    printf("usage: merlyx [options...]\n");
    printf("\n");
    printf("options:\n");
    printf("   -c,          display information for the CPU\n");
    printf("   -g,          display information for the GPU\n");
    printf("   -m,          display information for the memory\n");
    printf("   -n,          display information for the network interfaces\n");
    printf("   -x,          write informations in HTML format\n");
    printf("   -h,          display help\n");
    printf("   -o FILE,     write informations into FILE\n");
}

int main(int argc, char * argv[])
{
    int option;
    CPUID_INFO info;
    char options[7], odefault=1;
    char * liste_option = "cgmnxho:";
    FILE * output=stdout;

    opterr = 0; /* désactive les erreurs automatiques */

    for(option=0; option<6; ++option)
        options[option] = 0;

    while((option = getopt(argc, argv, liste_option)) != -1)
    {
        switch(option) {
            case 'c':
                if(odefault) odefault=0;
                options[0] = 1; break;
            case 'g':
                if(odefault) odefault=0;
                options[1] = 1; break;
            case 'm':
                if(odefault) odefault=0;
                options[2] = 1; break;
            case 'n':
                if(odefault) odefault=0;
                options[3] = 1; break;
            case 'x':
                options[4] = 1; break;
            case 'h':
                options[5] = 1; break;
            case 'o':
                options[6] = 1;
                output = fopen(optarg, "w"); break;
            case '?':
                usage(); exit(0);
            default:
                usage(); exit(0);
        }
    }

    if(options[5]){
        usage();
        exit(0);
    }

    if(odefault || options[0])
    {
        fprintf(output, "------ CPU ------\n");
        info = CPUID_INFO_create();
        CPUID_INFO_fprintf(output, info);
        CPUID_INFO_free(info);
        fprintf(output, "\n");
    }
    if(odefault || options[3])
    {
        fprintf(output, "------ Network ------\n");
        interface(output);
        fprintf(output, "\n");
    }
    if(output != stdout) fclose(output);

    return 0;
}
