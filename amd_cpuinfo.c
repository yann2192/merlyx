#include "amd_cpuinfo.h"

void amd_getProcessorInfo(amd_EAX1 * res)
{
    unsigned int e[4];
    asm("cpuid"
        : "=a" (e[0]),
        "=b" (e[1]),
        "=c" (e[2]),
        "=d" (e[3])
        : "a" (1)
        );
    res->stepping = e[0] & 0xF; /* 0-3 */
    res->model = (e[0] >> 0x4) & 0xF; /* 4-7 */
    res->family = (e[0] >> 0x8) & 0xF; /* 8-11 */
    /* NOTE: cpu type ???? */
    res->extendedmodel = (e[0] >> 0x10) & 0x7; /* 16-19 */
    res->extendedfamily = (e[0] >> 0x14) & 0xFF; /* 20-27 */

    res->brand_id = e[1] & 0xFF;
    res->chunks = (e[1] >> 0x8) & 0xFF;
    res->count = (e[1] >> 0x10) & 0xFF;
    res->apic_id = (e[1] >> 0x18) & 0xFF;

    res->sse3 = e[2] & 0x1;
    res->pclmuldq = (e[2] >> 0x1) & 0x1;
    res->monitor = (e[2] >> 0x3) & 0x1;
    res->ssse3 = (e[2] >> 0x9) & 0x1;
    res->fma = (e[2] >> 0xC) & 0x1;
    res->cx16 = (e[2] >> 0xD) & 0x1;
    res->sse41 = (e[2] >> 0x13) & 0x1;
    res->sse42 = (e[2] >> 0x14) & 0x1;
    res->popcnt = (e[2] >> 0x17) & 0x1;
    res->aes = (e[2] >> 0x19) & 0x1;
    res->xsave = (e[2] >> 0x1A) & 0x1;
    res->osxsave = (e[2] >> 0x1B) & 0x1;
    res->avx = (e[2] >> 0x1C) & 0x1;
    res->f16c = (e[2] >> 0x1D) & 0x1;

    res->fpu = e[3] & 0x1;
    res->vme = (e[3] >> 0x1) & 0x1;
    res->de = (e[3] >> 0x2) & 0x1;
    res->pse = (e[3] >> 0x3) & 0x1;
    res->tsc = (e[3] >> 0x4) & 0x1;
    res->msr = (e[3] >> 0x5) & 0x1;
    res->pae = (e[3] >> 0x6) & 0x1;
    res->mce = (e[3] >> 0x7) & 0x1;
    res->cx8 = (e[3] >> 0x8) & 0x1;
    res->apic = (e[3] >> 0x9) & 0x1;
    res->sep = (e[3] >> 0xB) & 0x1;
    res->mtrr = (e[3] >> 0xC) & 0x1;
    res->pge = (e[3] >> 0xD) & 0x1;
    res->mca = (e[3] >> 0xE) & 0x1;
    res->cmov = (e[3] >> 0xF) & 0x1;
    res->pat = (e[3] >> 0x10) & 0x1;
    res->pse_36 = (e[3] >> 0x11) & 0x1;
    res->clfsh = (e[3] >> 0x13) & 0x1;
    res->mmx = (e[3] >> 0x17) & 0x1;
    res->fxsr = (e[3] >> 0x18) & 0x1;
    res->sse = (e[3] >> 0x19) & 0x1;
    res->sse2 = (e[3] >> 0x1A) & 0x1;
    res->htt = (e[3] >> 0x1C) & 0x1;

    asm("cpuid"
        : "=a" (e[0]),
        "=b" (e[1]),
        "=c" (e[2]),
        "=d" (e[3])
        : "a" (0x80000002)
        );
    memcpy(res->cpuname, e, 16);
    asm("cpuid"
        : "=a" (e[0]),
        "=b" (e[1]),
        "=c" (e[2]),
        "=d" (e[3])
        : "a" (0x80000003)
        );
    memcpy(res->cpuname+16, e, 16);
    asm("cpuid"
        : "=a" (e[0]),
        "=b" (e[1]),
        "=c" (e[2]),
        "=d" (e[3])
        : "a" (0x80000004)
        );
    memcpy(res->cpuname+32, e, 16);
}

void amd_getCachesInfo(amd_EAX2 * res)
{
    unsigned int e[4];

    asm("cpuid"
        : "=a" (e[0]),
        "=b" (e[1]),
        "=c" (e[2]),
        "=d" (e[3])
        : "a" (0x80000005)
        );

    res->L1ITlb2and4MSize = e[0] & 0xFF;
    res->L1ITlb2and4MAssoc = (e[0] >> 8) & 0xFF;
    res->L1DTlb2and4MSize = (e[0] >> 16) & 0xFF;
    res->L1DTlb2and4MAssoc = (e[0] >> 24) & 0xFF;

    res->L1ITlb4KSize = e[1] & 0xFF;
    res->L1ITlb4KAssoc = (e[1] >> 8) & 0xFF;
    res->L1DTlb4KSize = (e[1] >> 16) & 0xFF;
    res->L1DTlb4KAssoc = (e[1] >> 24) & 0xFF;

    res->L1DcLineSize = e[2] & 0xFF;
    res->L1DcLinesPerTag = (e[2] >> 8) & 0xFF;
    res->L1DcAssoc = (e[2] >> 16) & 0xFF;
    res->L1DcSize = (e[2] >> 24) & 0xFF;

    res->L1IcLineSize = e[3] & 0xFF;
    res->L1IcLinesPerTag = (e[3] >> 8) & 0xFF;
    res->L1IcAssoc = (e[3] >> 16) & 0xFF;
    res->L1IcSize = (e[3] >> 24) & 0xFF;
}

void amd_getCachesParameters(amd_EAX4 * res)
{
    unsigned int e[4];
    unsigned int tmp;

    asm("cpuid"
        : "=a" (e[0]),
        "=b" (e[1]),
        "=c" (e[2]),
        "=d" (e[3])
        : "a" (0x80000006)
       );

    res->L2ITlb2and4MSize = e[0] & 0xFFF;
    tmp = (e[0] >> 12) & 0xF;
    switch(tmp) {
        case 0:
            res->L2ITlb2and4MAssoc = "L2/L3 cache or TLB is disabled"; break;
        case 1:
            res->L2ITlb2and4MAssoc = "Direct mapped"; break;
        case 2:
            res->L2ITlb2and4MAssoc = "2-way associative"; break;
        case 4:
            res->L2ITlb2and4MAssoc = "4-way associative"; break;
        case 6:
            res->L2ITlb2and4MAssoc = "8-way associative"; break;
        case 8:
            res->L2ITlb2and4MAssoc = "16-way associative"; break;
        case 0xA:
            res->L2ITlb2and4MAssoc = "32-way associative"; break;
        case 0xB:
            res->L2ITlb2and4MAssoc = "48-way associative"; break;
        case 0xC:
            res->L2ITlb2and4MAssoc = "64-way associative"; break;
        case 0xD:
            res->L2ITlb2and4MAssoc = "96-way associative"; break;
        case 0xE:
            res->L2ITlb2and4MAssoc = "128-way associative"; break;
        case 0xF:
            res->L2ITlb2and4MAssoc = "Fully associative"; break;
        default:
            res->L2ITlb2and4MAssoc = "Error !"; break;
    }
    res->L2DTlb2and4MSize = (e[0] >> 16) & 0xFFF;
    tmp = (e[0] >> 28) & 0xF;
    switch(tmp) {
        case 0:
            res->L2DTlb2and4MAssoc = "L2/L3 cache or TLB is disabled"; break;
        case 1:
            res->L2DTlb2and4MAssoc = "Direct mapped"; break;
        case 2:
            res->L2DTlb2and4MAssoc = "2-way associative"; break;
        case 4:
            res->L2DTlb2and4MAssoc = "4-way associative"; break;
        case 6:
            res->L2DTlb2and4MAssoc = "8-way associative"; break;
        case 8:
            res->L2DTlb2and4MAssoc = "16-way associative"; break;
        case 0xA:
            res->L2DTlb2and4MAssoc = "32-way associative"; break;
        case 0xB:
            res->L2DTlb2and4MAssoc = "48-way associative"; break;
        case 0xC:
            res->L2DTlb2and4MAssoc = "64-way associative"; break;
        case 0xD:
            res->L2DTlb2and4MAssoc = "96-way associative"; break;
        case 0xE:
            res->L2DTlb2and4MAssoc = "128-way associative"; break;
        case 0xF:
            res->L2DTlb2and4MAssoc = "Fully associative"; break;
        default:
            res->L2DTlb2and4MAssoc = "Error !"; break;
    }

    res->L2ITlb4KSize = e[1] & 0xFFF;
    tmp = (e[1] >> 12) & 0xF;
    switch(tmp) {
        case 0:
            res->L2ITlb4KAssoc = "L2/L3 cache or TLB is disabled"; break;
        case 1:
            res->L2ITlb4KAssoc = "Direct mapped"; break;
        case 2:
            res->L2ITlb4KAssoc = "2-way associative"; break;
        case 4:
            res->L2ITlb4KAssoc = "4-way associative"; break;
        case 6:
            res->L2ITlb4KAssoc = "8-way associative"; break;
        case 8:
            res->L2ITlb4KAssoc = "16-way associative"; break;
        case 0xA:
            res->L2ITlb4KAssoc = "32-way associative"; break;
        case 0xB:
            res->L2ITlb4KAssoc = "48-way associative"; break;
        case 0xC:
            res->L2ITlb4KAssoc = "64-way associative"; break;
        case 0xD:
            res->L2ITlb4KAssoc = "96-way associative"; break;
        case 0xE:
            res->L2ITlb4KAssoc = "128-way associative"; break;
        case 0xF:
            res->L2ITlb4KAssoc = "Fully associative"; break;
        default:
            res->L2ITlb4KAssoc = "Error !"; break;
    }
    res->L2DTlb4KSize = (e[1] >> 16) & 0xFFF;
    tmp = (e[1] >> 28) & 0xF;
    switch(tmp) {
        case 0:
            res->L2DTlb4KAssoc = "L2/L3 cache or TLB is disabled"; break;
        case 1:
            res->L2DTlb4KAssoc = "Direct mapped"; break;
        case 2:
            res->L2DTlb4KAssoc = "2-way associative"; break;
        case 4:
            res->L2DTlb4KAssoc = "4-way associative"; break;
        case 6:
            res->L2DTlb4KAssoc = "8-way associative"; break;
        case 8:
            res->L2DTlb4KAssoc = "16-way associative"; break;
        case 0xA:
            res->L2DTlb4KAssoc = "32-way associative"; break;
        case 0xB:
            res->L2DTlb4KAssoc = "48-way associative"; break;
        case 0xC:
            res->L2DTlb4KAssoc = "64-way associative"; break;
        case 0xD:
            res->L2DTlb4KAssoc = "96-way associative"; break;
        case 0xE:
            res->L2DTlb4KAssoc = "128-way associative"; break;
        case 0xF:
            res->L2DTlb4KAssoc = "Fully associative"; break;
        default:
            res->L2DTlb4KAssoc = "Error !"; break;
    }

    res->L2LineSize = e[2] & 0xFF;
    res->L2LinesPerTag = (e[2] >> 8) & 0xF;
    tmp = (e[2] >> 12) & 0xF;
    switch(tmp) {
        case 0:
            res->L2Assoc = "L2/L3 cache or TLB is disabled"; break;
        case 1:
            res->L2Assoc = "Direct mapped"; break;
        case 2:
            res->L2Assoc = "2-way associative"; break;
        case 4:
            res->L2Assoc = "4-way associative"; break;
        case 6:
            res->L2Assoc = "8-way associative"; break;
        case 8:
            res->L2Assoc = "16-way associative"; break;
        case 0xA:
            res->L2Assoc = "32-way associative"; break;
        case 0xB:
            res->L2Assoc = "48-way associative"; break;
        case 0xC:
            res->L2Assoc = "64-way associative"; break;
        case 0xD:
            res->L2Assoc = "96-way associative"; break;
        case 0xE:
            res->L2Assoc = "128-way associative"; break;
        case 0xF:
            res->L2Assoc = "Fully associative"; break;
        default:
            res->L2Assoc = "Error !"; break;
    }
    res->L2Size = (e[2] >> 16) & 0xFFFF;

    res->L3LineSize = e[3] & 0xFF;
    res->L3LinesPerTag = (e[3] >> 8) & 0xF;
    tmp = (e[3] >> 12) & 0xF;
    switch(tmp) {
        case 0:
            res->L3Assoc = "L2/L3 cache or TLB is disabled"; break;
        case 1:
            res->L3Assoc = "Direct mapped"; break;
        case 2:
            res->L3Assoc = "2-way associative"; break;
        case 4:
            res->L3Assoc = "4-way associative"; break;
        case 6:
            res->L3Assoc = "8-way associative"; break;
        case 8:
            res->L3Assoc = "16-way associative"; break;
        case 0xA:
            res->L3Assoc = "32-way associative"; break;
        case 0xB:
            res->L3Assoc = "48-way associative"; break;
        case 0xC:
            res->L3Assoc = "64-way associative"; break;
        case 0xD:
            res->L3Assoc = "96-way associative"; break;
        case 0xE:
            res->L3Assoc = "128-way associative"; break;
        case 0xF:
            res->L3Assoc = "Fully associative"; break;
        default:
            res->L3Assoc = "Error !"; break;
    }
    res->L3Size = (e[3] >> 18) & 0x3FFF;
}

void amd_getProcessorTopology(amd_EAXB * res)
{
    unsigned int e[4];

    asm("cpuid"
        : "=a" (e[0]),
        "=b" (e[1]),
        "=c" (e[2]),
        "=d" (e[3])
        : "a" (0x80000008)
       );

    res->cpu_count = e[2] & 0xFF;
}

void amd_CPUID_INFO2_free(amd_EAX1 * res) {}

void amd_CPUID_INFO3_free(amd_EAX2 * res) {}

void amd_CPUID_INFO4_free(amd_EAX4 * res) {}

void amd_CPUID_INFO5_free(amd_EAXB * res) {}

void amd_CPUID_INFO2_fprintf(FILE * f, amd_EAX1 * info2)
{
    int a = 0;

    fprintf(f, "Processor Brand String                     : %s\n", info2->cpuname);
    fprintf(f, "Stepping                                   : 0x%x\n", info2->stepping);
    fprintf(f, "Model                                      : 0x%x\n", info2->model);
    fprintf(f, "Family                                     : 0x%x\n", info2->family);
    fprintf(f, "Extended model                             : 0x%x\n", info2->extendedmodel);
    fprintf(f, "Extended family                            : 0x%x\n\n", info2->extendedfamily);

    fprintf(f, "Brand ID                : 0x%x\n", info2->brand_id);
    fprintf(f, "Chunks                  : 0x%x\n", info2->chunks);
    fprintf(f, "Logical Processor Count : 0x%x (%d)\n", info2->count, info2->count);
    fprintf(f, "APIC ID                 : 0x%x\n\n", info2->apic_id);

    fprintf(f, "Features supported :\n");

    if(info2->sse3){ fprintf(f, "SSE3 "); ++a; }
    if(info2->pclmuldq){ fprintf(f, "PCLMULDQ "); ++a; }
    if(info2->monitor){ fprintf(f, "MONITOR "); ++a; }
    if(info2->ssse3){ fprintf(f, "SSSE3 "); ++a; }
    if(info2->fma){ fprintf(f, "FMA "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->cx16){ fprintf(f, "CX16 "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->sse41){ fprintf(f, "SSE4.1 "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->sse42){ fprintf(f, "SSE4.2 "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->popcnt){ fprintf(f, "POPCNT "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->aes){ fprintf(f, "AES "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->xsave){ fprintf(f, "XSAVE "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->osxsave){ fprintf(f, "OSXSAVE "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->avx){ fprintf(f, "AVX "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->f16c){ fprintf(f, "F16C "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }

    if(info2->fpu){ fprintf(f, "FPU "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->vme){ fprintf(f, "VME "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->de){ fprintf(f, "DE "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->pse){ fprintf(f, "PSE "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->tsc){ fprintf(f, "TSC "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->msr){ fprintf(f, "MSR "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->pae){ fprintf(f, "PAE "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->mce){ fprintf(f, "MCE "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->cx8){ fprintf(f, "CX8 "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->apic){ fprintf(f, "APIC "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->sep){ fprintf(f, "SEP "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->mtrr){ fprintf(f, "MTRR "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->pge){ fprintf(f, "PGE "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->mca){ fprintf(f, "MCA "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->cmov){ fprintf(f, "CMOV "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->pat){ fprintf(f, "PAT "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->pse_36){ fprintf(f, "PSE-36 "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->clfsh){ fprintf(f, "CLFSH "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->mmx){ fprintf(f, "MMX "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->fxsr){ fprintf(f, "FXSR "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->sse){ fprintf(f, "SSE "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->sse2){ fprintf(f, "SSE2 "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->htt){ fprintf(f, "HTT "); ++a; }
    fprintf(f, "\n");
}

void amd_CPUID_INFO3_fprintf(FILE * f, amd_EAX2 * info3)
{
    fprintf(f, " ------ L1 Cache and TLB Identifiers ------\n");
    fprintf(f, "Data TLB associativity for 2 MB and 4 MB pages : 0x%x\n", info3->L1DTlb2and4MAssoc);
    fprintf(f, "Data TLB number of entries for 2 MB and 4 MB pages : 0x%x\n", info3->L1DTlb2and4MSize);
    fprintf(f, "Instruction TLB associativity for 2 MB and 4 MB pages : 0x%x\n", info3->L1ITlb2and4MAssoc);
    fprintf(f, "Instruction TLB number of entries for 2 MB and 4 MB pages : 0x%x\n", info3->L1ITlb2and4MSize);
    fprintf(f, "\n");
    fprintf(f, "Data TLB associativity for 4 KB pages : 0x%x\n", info3->L1DTlb4KAssoc);
    fprintf(f, "Data TLB number of entries for 4 KB pages : 0x%x\n", info3->L1DTlb4KSize);
    fprintf(f, "Instruction TLB associativity for 4 KB pages : 0x%x\n", info3->L1ITlb4KAssoc);
    fprintf(f, "Instruction TLB number of entries for 4 KB pages : 0x%x\n", info3->L1ITlb4KSize);
    fprintf(f, "\n");
    fprintf(f, "L1 data cache size in KB : 0x%x\n", info3->L1DcSize);
    fprintf(f, "L1 data cache associativity : 0x%x\n", info3->L1DcAssoc);
    fprintf(f, "L1 data cache lines per tag : 0x%x\n", info3->L1DcLinesPerTag);
    fprintf(f, "L1 data cache line size in bytes : 0x%x\n", info3->L1DcLineSize);
    fprintf(f, "\n");
    fprintf(f, "L1 instruction cache size KB : 0x%x\n", info3->L1IcSize);
    fprintf(f, "L1 instruction cache associativity : 0x%x\n", info3->L1IcAssoc);
    fprintf(f, "L1 instruction cache lines per tag : 0x%x\n", info3->L1IcLinesPerTag);
    fprintf(f, "L1 instruction cache line size in bytes : 0x%x\n", info3->L1IcLineSize);
    fprintf(f, "\n");
}

void amd_CPUID_INFO4_fprintf(FILE * f, amd_EAX4 * info4)
{
    fprintf(f, " ------ L2/L3 Cache and TLB Identifiers ------\n");
    fprintf(f, "L2 data TLB associativity for 2 MB and 4 MB pages : %s\n", info4->L2DTlb2and4MAssoc);
    fprintf(f, "L2 data TLB number of entries for 2 MB and 4 MB pages : 0x%x\n", info4->L2DTlb2and4MSize);
    fprintf(f, "L2 instruction TLB associativity for 2 MB and 4 MB pages : %s\n", info4->L2ITlb2and4MAssoc);
    fprintf(f, "L2 instruction TLB number of entries for 2 MB and 4 MB pages : 0x%x\n", info4->L2ITlb2and4MSize);
    fprintf(f, "\n");
    fprintf(f, "L2 data TLB associativity for 4 KB pages : %s\n", info4->L2DTlb4KAssoc);
    fprintf(f, "L2 data TLB number of entries for 4 KB pages : 0x%x\n", info4->L2DTlb4KSize);
    fprintf(f, "L2 instruction TLB associativity for 4 KB pages : %s\n", info4->L2ITlb4KAssoc);
    fprintf(f, "L2 instruction TLB number of entries for 4 KB pages : 0x%x\n", info4->L2ITlb4KSize);
    fprintf(f, "\n");
    fprintf(f, "L2 cache size in KB : 0x%x\n", info4->L2Size);
    fprintf(f, "L2 cache associativity : %s\n", info4->L2Assoc);
    fprintf(f, "L2 cache lines per tag : 0x%x\n", info4->L2LinesPerTag);
    fprintf(f, "L2 cache line size in bytes : 0x%x\n", info4->L2LineSize);
    fprintf(f, "\n");
    fprintf(f, "L3 cache size in KB : 0x%x\n", info4->L3Size);
    fprintf(f, "L3 cache associativity : %s\n", info4->L3Assoc);
    fprintf(f, "L3 cache lines per tag : 0x%x\n", info4->L3LinesPerTag);
    fprintf(f, "L3 cache line size in bytes : 0x%x\n", info4->L3LineSize);
    fprintf(f, "\n");
}

void amd_CPUID_INFO5_fprintf(FILE * f, amd_EAXB * info5)
{
    fprintf(f, "Number of physical cores : %d\n", info5->cpu_count);
    fprintf(f, "\n");
}
