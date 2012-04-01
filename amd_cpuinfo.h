#ifndef __AMD_CPUINFO_H__
#define __AMD_CPUINFO_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct amd_eax1
{
    char cpuname[48];

    unsigned char stepping;
    unsigned char model;
    unsigned char family;
    /*char * cputype;*/
    unsigned char extendedmodel;
    unsigned short extendedfamily;

    unsigned char brand_id;
    unsigned char chunks;
    unsigned char count;
    unsigned char apic_id;

    unsigned char sse3;
    unsigned char pclmuldq;
    unsigned char monitor;
    unsigned char ssse3;
    unsigned char fma;
    unsigned char cx16;
    unsigned char sse41;
    unsigned char sse42;
    unsigned char popcnt;
    unsigned char aes;
    unsigned char xsave;
    unsigned char osxsave;
    unsigned char avx;
    unsigned char f16c;

    unsigned char fpu;
    unsigned char vme;
    unsigned char de;
    unsigned char pse;
    unsigned char tsc;
    unsigned char msr;
    unsigned char pae;
    unsigned char mce;
    unsigned char cx8;
    unsigned char apic;
    unsigned char sep;
    unsigned char mtrr;
    unsigned char pge;
    unsigned char mca;
    unsigned char cmov;
    unsigned char pat;
    unsigned char pse_36;
    unsigned char clfsh;
    unsigned char mmx;
    unsigned char fxsr;
    unsigned char sse;
    unsigned char sse2;
    unsigned char htt;
};

typedef struct amd_eax1 amd_EAX1;

struct amd_eax2
{
    unsigned short L1DTlb2and4MAssoc;
    unsigned short L1DTlb2and4MSize;
    unsigned short L1ITlb2and4MAssoc;
    unsigned short L1ITlb2and4MSize;

    unsigned short L1DTlb4KAssoc;
    unsigned short L1DTlb4KSize;
    unsigned short L1ITlb4KAssoc;
    unsigned short L1ITlb4KSize;

    unsigned short L1DcSize;
    unsigned short L1DcAssoc;
    unsigned short L1DcLinesPerTag;
    unsigned short L1DcLineSize;

    unsigned short L1IcSize;
    unsigned short L1IcAssoc;
    unsigned short L1IcLinesPerTag;
    unsigned short L1IcLineSize;
};
typedef struct amd_eax2 amd_EAX2;

struct amd_eax4
{
    char * L2DTlb2and4MAssoc;
    unsigned short L2DTlb2and4MSize;
    char * L2ITlb2and4MAssoc;
    unsigned short L2ITlb2and4MSize;

    char * L2DTlb4KAssoc;
    unsigned short L2DTlb4KSize;
    char * L2ITlb4KAssoc;
    unsigned short L2ITlb4KSize;

    unsigned short L2Size;
    char * L2Assoc;
    unsigned short L2LinesPerTag;
    unsigned short L2LineSize;

    unsigned short L3Size;
    char * L3Assoc;
    unsigned short L3LinesPerTag;
    unsigned short L3LineSize;
};
typedef struct amd_eax4 amd_EAX4;

struct amd_eaxb
{
    unsigned short cpu_count;
};
typedef struct amd_eaxb amd_EAXB;

void amd_getProcessorInfo(amd_EAX1 *);

void amd_getCachesInfo(amd_EAX2 *);

void amd_getCachesParameters(amd_EAX4 *);

void amd_getProcessorTopology(amd_EAXB *);

void amd_CPUID_INFO2_free(amd_EAX1 *);

void amd_CPUID_INFO3_free(amd_EAX2 *);

void amd_CPUID_INFO4_free(amd_EAX4 *);

void amd_CPUID_INFO5_free(amd_EAXB *);

void amd_CPUID_INFO2_fprintf(FILE * f, amd_EAX1 *);

void amd_CPUID_INFO3_fprintf(FILE * f, amd_EAX2 *);

void amd_CPUID_INFO4_fprintf(FILE * f, amd_EAX4 *);

void amd_CPUID_INFO5_fprintf(FILE * f, amd_EAXB *);

#endif
