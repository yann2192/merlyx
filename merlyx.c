#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cpuinfo.h"
#include "network.h"
#include "memory.h"
#include "get_uname.h"
#include "gpunvidia.h"
#include "output.h"


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
    printf("   -k,          display information for the Kernel\n");
}

int main(int argc, char * argv[])
{
    int option;
    CPUID_INFO info;
    char options[8], odefault=1;
    char * liste_option = "cgmnxho:k";
    FILE * output=stdout;

    opterr = 0; /* désactive les erreurs automatiques */

    for(option=0; option<8; ++option)
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
                output = fopen(optarg, "w");
                if(!output) {
                    printf("Fail to open %s\n", optarg);
                    usage();
                    exit(0);
                }
                break;
            case 'k':
                if(odefault) odefault=0;
                options[7] = 1; break;
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
    init_output(output, options[4]);
    if(odefault || options[7])
    {
        get_uname(output, options[4]);
    }
    if(odefault || options[0])
    {
        print_title(output, options[4], "CPU");
        info = CPUID_INFO_create();
        CPUID_INFO_fprintf(output, info, options[4]);
        CPUID_INFO_free(info);
    }
    if(odefault || options[1])
    {
        print_title(output, options[4], "GPU");
        getNvidiaInfo(output, options[4]);
    }
    if(odefault || options[2])
    {
        print_title(output, options[4], "Memory");
        memory_usage(output, options[4]);
    }
    if(odefault || options[3])
    {
        print_title(output, options[4], "Network");
        interfaces(output, options[4]);
    }
    end_output(output, options[4]);
    if(options[6]) fclose(output);

    return 0;
}
