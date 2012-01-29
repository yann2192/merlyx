#include "cpuinfo.h"

static void getVendor(EAX0 * res)
{
    int * t = (int *)res->vendor;
    asm("xor %%rax, %%rax\n"
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

static void getProcessorInfo(EAX1 * res)
{
    int e[4];
    asm("mov $1, %%rax\n"
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
    res->model = e[0] & 0xF0; /* 4-7 */
    res->family = e[0] & 0xF00; /* 8-11 */
    res->cputype = e[0] & 0x3000; /* 12-13 */
    res->extendedmodel = e[0] & 0xF0000; /* 16-19 */
    res->extendedfamily = e[0] & 0xFF00000; /* 20-27 */
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
    fprintf(f, "Largest Standard Function Number Supported : %i\n", info->info1.lsfns);
    fprintf(f, "Vendor : %s\n\n", info->info1.vendor);
    fprintf(f, "Stepping : %i\n", info->info2.stepping);
    fprintf(f, "Model : %i\n", info->info2.model);
    fprintf(f, "Family : %i\n", info->info2.family);
    fprintf(f, "CPU type : ");
    switch(info->info2.cputype){
        case 0: fprintf(f, "Original\n"); break;
        case 1: fprintf(f, "OverDrive\n"); break;
        case 2: fprintf(f, "Dual\n"); break;
        default: fprintf(f, "Unknown (%i)\n", info->info2.cputype);
    }
    fprintf(f, "Extended model : %i\n", info->info2.extendedmodel);
    fprintf(f, "Extended family : %i\n", info->info2.extendedfamily);
}
