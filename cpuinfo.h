#ifndef __CPUINFO_H__
#define __CPUINFO_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "intel_cpuinfo.h"
#include "amd_cpuinfo.h"

struct eax0
{
    unsigned int lsfns; /* Largest Standard Function Number Supported */
    char vendor[13];
};

typedef struct eax0 EAX0;

struct cpuid_info
{
    EAX0 info1;
    union {
        intel_EAX1 intel;
        amd_EAX1 amd;
    } info2;
    union {
        intel_EAX2 intel;
        amd_EAX2 amd;
    } info3;
    union {
        intel_EAX4 intel;
        amd_EAX4 amd;
    } info4;
    union {
        intel_EAXB intel;
        void * amd;
    } info5;
};

typedef struct cpuid_info * CPUID_INFO;

void getVendor(EAX0 *);

CPUID_INFO CPUID_INFO_create();

void CPUID_INFO_free(CPUID_INFO p);

void CPUID_INFO_fprintf(FILE * f, CPUID_INFO info);

#endif
