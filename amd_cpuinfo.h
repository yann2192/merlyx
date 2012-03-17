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

    /*unsigned char lahfsahf;
    unsigned char cmplegacy;
    unsigned char svm;
    unsigned char extapicspace;
    unsigned char altmovcr8;
    unsigned char abm;
    unsigned char sse4a;
    unsigned char misalignsse;
    unsigned char 3dnowprefetch;
    unsigned char osvw;
    unsigned char ibs;
    unsigned char xop;
    unsigned char skinit;
    unsigned char fma4;
    unsigned char nodeid;
    unsigned char tbm;
    unsigned char topologyextensions;

    unsigned char nx;
    unsigned char mmxext;
    unsigned char ffxsr;
    unsigned char page1gb;
    unsigned char rdtscp;
    unsigned char lm;
    unsigned char 3dnowext;
    unsigned char 3dnow;*/
};

typedef struct amd_eax1 amd_EAX1;

struct amd_eax2
{
    char * caches[15]; /* NOTE: maybe change */
};
typedef struct amd_eax2 amd_EAX2;

struct amd_eax4
{
    char * cache_type;
    unsigned char cache_level;
    unsigned char sicl;
    unsigned char fac;
    unsigned short mntstc;
    unsigned char napicidrtp;

    unsigned short scls;
    unsigned short plp;
    unsigned short woa;

    unsigned int nsets;

    unsigned char wbinvd;
    unsigned char ciitlcl;
    unsigned char cci;

    unsigned short cache_size;

    struct amd_eax4 * next;
};
typedef struct amd_eax4 amd_EAX4;

void amd_getProcessorInfo(amd_EAX1 *);

void amd_getCachesInfo(amd_EAX2 *);

void amd_getCachesParameters(amd_EAX4 *);

void amd_CPUID_INFO2_free(amd_EAX1 *);

void amd_CPUID_INFO3_free(amd_EAX2 *);

void amd_CPUID_INFO4_free(amd_EAX4 *);

void amd_CPUID_INFO2_fprintf(FILE * f, amd_EAX1 *);

void amd_CPUID_INFO3_fprintf(FILE * f, amd_EAX2 *);

void amd_CPUID_INFO4_fprintf(FILE * f, amd_EAX4 *);

#endif
