#include "cpuinfo.h"

int main(int argc, const char *argv[])
{
    CPUID_INFO info = CPUID_INFO_create();
    CPUID_INFO_fprintf(stdout, info);
    CPUID_INFO_free(info);
    return 0;
}
