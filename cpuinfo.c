#include "cpuinfo.h"

void getVendor(EAX0 * res)
{
    unsigned int * t = (unsigned int *)res->vendor;
    asm("xor %%eax, %%eax\n"
        "cpuid\n"
        "mov %%eax, %0\n"
        "mov %%ebx, %1\n"
        "mov %%edx, %2\n"
        "mov %%ecx, %3\n"
        : "=r" (res->lsfns), "=r" (t[0]), "=r" (t[1]), "=r" (t[2]) /* OUTPUT */
        : /* INPUT */
        : "%eax", "%ebx", "%ecx", "edx" /* clobbered register */
       );
    res->vendor[12] = '\0';
}

void getProcessorInfo(EAX1 * res)
{
    unsigned int e[4];
    asm("mov $1, %%eax\n"
        "cpuid\n"
        "mov %%eax, %0\n"
        "mov %%ebx, %1\n"
        "mov %%ecx, %2\n"
        "mov %%edx, %3\n"
        : "=r" (e[0]), "=r" (e[1]), "=r" (e[2]), "=r" (e[3]) /* OUTPUT */
        : /* INPUT */
        : "%eax", "%ebx", "%ecx", "edx" /* clobbered register */
       );
    res->stepping = e[0] & 0xF; /* 0-3 */
    res->model = (e[0] >> 0x4) & 0xF; /* 4-7 */
    res->family = (e[0] >> 0x8) & 0xF; /* 8-11 */
    res->cputype = (e[0] >> 0xC) & 0x3; /* 12-13 */
    res->extendedmodel = (e[0] >> 0x10) & 0x7; /* 16-19 */
    res->extendedfamily = (e[0] >> 0x14) & 0xFF; /* 20-27 */
}

CPUID_INFO CPUID_INFO_create()
{
    CPUID_INFO res = malloc(sizeof(struct cpuid_info));
    getVendor(&(res->info1));
    getProcessorInfo(&(res->info2));
    return res;
}

void CPUID_INFO_free(CPUID_INFO p)
{
    free(p);
}

void CPUID_INFO_fprintf(FILE * f, CPUID_INFO info)
{
    fprintf(f, "Largest Standard Function Number Supported : 0x%x\n", info->info1.lsfns);
    fprintf(f, "Vendor : %s\n\n", info->info1.vendor);
    fprintf(f, "Stepping : 0x%x\n", info->info2.stepping);
    fprintf(f, "Model : 0x%x\n", info->info2.model);
    fprintf(f, "Family : 0x%x\n", info->info2.family);
    fprintf(f, "CPU type : ");
    switch(info->info2.cputype){
        case 0: fprintf(f, "Original\n"); break;
        case 1: fprintf(f, "OverDrive\n"); break;
        case 2: fprintf(f, "Dual\n"); break;
        default: fprintf(f, "Unknown (%i)\n", info->info2.cputype);
    }
    fprintf(f, "Extended model : 0x%x\n", info->info2.extendedmodel);
    fprintf(f, "Extended family : 0x%x\n", info->info2.extendedfamily);
}
