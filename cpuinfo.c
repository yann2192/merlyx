#include "cpuinfo.h"

void getVendor(EAX0 * res)
{
    unsigned int e[4];
    asm("cpuid"
        : "=a" (e[0]),
        "=b" (e[1]),
        "=c" (e[2]),
        "=d" (e[3])
        : "a" (0)
        );
    res->lsfns = e[0];
    memcpy((res->vendor), e+1, 4);
    memcpy((res->vendor)+8, e+2, 4);
    memcpy((res->vendor)+4, e+3, 4);
    res->vendor[12] = '\0';
}

CPUID_INFO CPUID_INFO_create()
{
    CPUID_INFO res = malloc(sizeof(struct cpuid_info));
    getVendor(&(res->info1));
    if(!strncmp(res->info1.vendor, "GenuineIntel", 12)){
        intel_getProcessorInfo(&(res->info2.intel));
        intel_getCachesInfo(&(res->info3.intel));
        intel_getCachesParameters(&(res->info4.intel));
        intel_getProcessorTopology(&(res->info5.intel));
    } else if(!strncmp(res->info1.vendor, "AuthenticAMD", 12)) {
        amd_getProcessorInfo(&(res->info2.amd));
        amd_getCachesInfo(&(res->info3.amd));
        amd_getCachesParameters(&(res->info4.amd));
        amd_getProcessorTopology(&(res->info5.amd));
    }
    return res;
}

void CPUID_INFO_free(CPUID_INFO p)
{
    if(!strncmp(p->info1.vendor, "GenuineIntel", 12)){
        intel_CPUID_INFO2_free(&(p->info2.intel));
        intel_CPUID_INFO3_free(&(p->info3.intel));
        intel_CPUID_INFO4_free(&(p->info4.intel));
        intel_CPUID_INFO5_free(&(p->info5.intel));
    } else if(!strncmp(p->info1.vendor, "AuthenticAMD", 12)) {
        amd_CPUID_INFO2_free(&(p->info2.amd));
        amd_CPUID_INFO3_free(&(p->info3.amd));
        amd_CPUID_INFO4_free(&(p->info4.amd));
        amd_CPUID_INFO5_free(&(p->info5.amd));
    }
    free(p);
}

void CPUID_INFO_fprintf(FILE * f, CPUID_INFO p, char html)
{
    print(f, html, "Largest Standard Function Number Supported : 0x%x", p->info1.lsfns);
    print(f, html, "Vendor                                     : %s", p->info1.vendor);
    print_nl(f, html);
    if(!strncmp(p->info1.vendor, "GenuineIntel", 12)){
        intel_CPUID_INFO2_fprintf(f, &(p->info2.intel), html);
        intel_CPUID_INFO3_fprintf(f, &(p->info3.intel), html);
        intel_CPUID_INFO4_fprintf(f, &(p->info4.intel), html);
        intel_CPUID_INFO5_fprintf(f, &(p->info5.intel), html);
    } else if(!strncmp(p->info1.vendor, "AuthenticAMD", 12)) {
        amd_CPUID_INFO2_fprintf(f, &(p->info2.amd), html);
        amd_CPUID_INFO3_fprintf(f, &(p->info3.amd), html);
        amd_CPUID_INFO4_fprintf(f, &(p->info4.amd), html);
        amd_CPUID_INFO5_fprintf(f, &(p->info5.amd), html);
    } else {
        print(f, html, ">> unknown Processor !");
    }
}
