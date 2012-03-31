#ifndef __INTEL_CPUINFO_H__
#define __INTEL_CPUINFO_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct intel_eax1
{
    char cpuname[48];

    unsigned char stepping;
    unsigned char model;
    unsigned char family;
    char * cputype;
    unsigned char extendedmodel;
    unsigned short extendedfamily;

    unsigned char brand_id;
    unsigned char chunks;
    unsigned char count;
    unsigned char apic_id;

    unsigned char sse3;
    unsigned char pclmuldq;
    unsigned char dtes64;
    unsigned char monitor;
    unsigned char ds_cpl;
    unsigned char vmx;
    unsigned char smx;
    unsigned char eist;
    unsigned char tm2;
    unsigned char ssse3;
    unsigned char cnxt_id;
    unsigned char fma;
    unsigned char cx16;
    unsigned char xtpr;
    unsigned char pdcm;
    unsigned char pcid;
    unsigned char dca;
    unsigned char sse41;
    unsigned char sse42;
    unsigned char x2apic;
    unsigned char movbe;
    unsigned char popcnt;
    unsigned char tsc_deadline;
    unsigned char aes;
    unsigned char xsave;
    unsigned char osxsave;
    unsigned char avx;

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
    unsigned char psn;
    unsigned char clfsh;
    unsigned char ds;
    unsigned char acpi;
    unsigned char mmx;
    unsigned char fxsr;
    unsigned char sse;
    unsigned char sse2;
    unsigned char ss;
    unsigned char htt;
    unsigned char tm;
    unsigned char pbe;
};

typedef struct intel_eax1 intel_EAX1;

struct intel_eax2
{
    char * caches[15]; /* NOTE: maybe change */
};
typedef struct intel_eax2 intel_EAX2;

struct intel_eax4
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

    unsigned int cache_size;

    struct intel_eax4 * next;
};
typedef struct intel_eax4 intel_EAX4;

void intel_getProcessorInfo(intel_EAX1 *);

void intel_getCachesInfo(intel_EAX2 *);

void intel_getCachesParameters(intel_EAX4 *);

void intel_CPUID_INFO2_free(intel_EAX1 *);

void intel_CPUID_INFO3_free(intel_EAX2 *);

void intel_CPUID_INFO4_free(intel_EAX4 *);

void intel_CPUID_INFO2_fprintf(FILE * f, intel_EAX1 *);

void intel_CPUID_INFO3_fprintf(FILE * f, intel_EAX2 *);

void intel_CPUID_INFO4_fprintf(FILE * f, intel_EAX4 *);

#endif
