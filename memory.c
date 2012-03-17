#include "memory.h"

void memory_usage(FILE * f)
{
    FILE * mem;
    char buffer[1025];

    mem = fopen("/proc/meminfo", "r");
    memset(buffer, 0, 1025);
    while(fread(buffer, 1, 1024, mem)) {
        fprintf(f, "%s", buffer);
        memset(buffer, 0, 1025);
    }
    fclose(mem);
}
