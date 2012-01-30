#ifndef __CPUINFO_H__
#define __CPUINFO_H__

#include <stdlib.h>
#include <stdio.h>

struct eax0
{
    unsigned int lsfns; /* Largest Standard Function Number Supported */
    char vendor[13];
};

typedef struct eax0 EAX0;

struct eax1
{
    unsigned short stepping;
    unsigned short model;
    unsigned short family;
    unsigned short cputype;
    unsigned int extendedmodel;
    unsigned int extendedfamily;
};

typedef struct eax1 EAX1;

struct cpuid_info
{
    EAX0 info1;
    EAX1 info2;
};

typedef struct cpuid_info * CPUID_INFO;

void getVendor(EAX0 *);

void getProcessorInfo(EAX1 *);

CPUID_INFO CPUID_INFO_create();

void CPUID_INFO_free(CPUID_INFO p);

void CPUID_INFO_fprintf(FILE * f, CPUID_INFO info);

#endif
