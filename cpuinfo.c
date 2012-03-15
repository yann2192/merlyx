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

    res->brand_id = e[1] & 0xFF;
    res->chunks = (e[1] >> 0x8) & 0xFF;
    res->count = (e[1] >> 0x10) & 0xFF;
    res->apic_id = (e[1] >> 0x18) & 0xFF;

    res->sse3 = e[2] & 0x1;
    res->pclmuldq = (e[2] >> 0x1) & 0x1;
    res->dtes64 = (e[2] >> 0x2) & 0x1;
    res->monitor = (e[2] >> 0x3) & 0x1;
    res->ds_cpl = (e[2] >> 0x4) & 0x1;
    res->vmx = (e[2] >> 0x5) & 0x1;
    res->smx = (e[2] >> 0x6) & 0x1;
    res->eist = (e[2] >> 0x7) & 0x1;
    res->tm2 = (e[2] >> 0x8) & 0x1;
    res->ssse3 = (e[2] >> 0x9) & 0x1;
    res->cnxt_id = (e[2] >> 0xA) & 0x1;
    res->fma = (e[2] >> 0xC) & 0x1;
    res->cx16 = (e[2] >> 0xD) & 0x1;
    res->xtpr = (e[2] >> 0xE) & 0x1;
    res->pdcm = (e[2] >> 0xF) & 0x1;
    res->pcid = (e[2] >> 0x11) & 0x1;
    res->dca = (e[2] >> 0x12) & 0x1;
    res->sse41 = (e[2] >> 0x13) & 0x1;
    res->sse42 = (e[2] >> 0x14) & 0x1;
    res->x2apic = (e[2] >> 0x15) & 0x1;
    res->movbe = (e[2] >> 0x16) & 0x1;
    res->popcnt = (e[2] >> 0x17) & 0x1;
    res->tsc_deadline = (e[2] >> 0x18) & 0x1;
    res->aes = (e[2] >> 0x19) & 0x1;
    res->xsave = (e[2] >> 0x1A) & 0x1;
    res->osxsave = (e[2] >> 0x1B) & 0x1;
    res->avx = (e[2] >> 0x1C) & 0x1;

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
    res->psn = (e[3] >> 0x12) & 0x1;
    res->clfsh = (e[3] >> 0x13) & 0x1;
    res->ds = (e[3] >> 0x15) & 0x1;
    res->acpi = (e[3] >> 0x16) & 0x1;
    res->mmx = (e[3] >> 0x17) & 0x1;
    res->fxsr = (e[3] >> 0x18) & 0x1;
    res->sse = (e[3] >> 0x19) & 0x1;
    res->sse2 = (e[3] >> 0x1A) & 0x1;
    res->ss = (e[3] >> 0x1B) & 0x1;
    res->htt = (e[3] >> 0x1C) & 0x1;
    res->tm = (e[3] >> 0x1D) & 0x1;
    res->pbe = (e[3] >> 0x1F) & 0x1;
}

void getCachesInfo(EAX2 * res)
{
    unsigned int e[4];
    int nb, i;
    asm("mov $2, %%eax\n"
        "cpuid\n"
        "mov %%eax, %0\n"
        "mov %%ebx, %1\n"
        "mov %%ecx, %2\n"
        "mov %%edx, %3\n"
        : "=r" (e[0]), "=r" (e[1]), "=r" (e[2]), "=r" (e[3]) /* OUTPUT */
        : /* INPUT */
        : "%eax", "%ebx", "%ecx", "edx" /* clobbered register */
       );

    nb = e[0] & 0xFF;
    printf("nb => 0x%x\n", nb);
    for(i=1; i < 15; ++i)
        res->caches[i-1] = (e[0] >> 0x8*i) & 0xFF;
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
    fprintf(f, "Processor type : ");
    switch(info->info2.cputype){
        case 0: fprintf(f, "Original OEM Processor (0x0)\n"); break;
        case 1: fprintf(f, "OverDrive Processor (0x1)\n"); break;
        case 2: fprintf(f, "Dual Processor (0x2)\n"); break;
        default: fprintf(f, "Unknown (0x%x)\n", info->info2.cputype);
    }
    fprintf(f, "Extended model : 0x%x\n", info->info2.extendedmodel);
    fprintf(f, "Extended family : 0x%x\n\n", info->info2.extendedfamily);
    fprintf(f, "Brand ID : 0x%x\n", info->info2.brand_id);
    fprintf(f, "Chunks : 0x%x\n", info->info2.chunks);
    fprintf(f, "Logical Processor Count : 0x%x (%d)\n", info->info2.count, info->info2.count);
    fprintf(f, "APIC ID : 0x%x\n\n", info->info2.apic_id);

    fprintf(f, "SSE3 : %s\n", info->info2.sse3 ? "true" : "false");
    fprintf(f, "PCLMULDQ : %s\n", info->info2.pclmuldq ? "true" : "false");
    fprintf(f, "DTES64 : %s\n", info->info2.dtes64 ? "true" : "false");
    fprintf(f, "MONITOR : %s\n", info->info2.monitor ? "true" : "false");
    fprintf(f, "DS-CPL : %s\n", info->info2.ds_cpl ? "true" : "false");
    fprintf(f, "VMX : %s\n", info->info2.vmx ? "true" : "false");
    fprintf(f, "SMX : %s\n", info->info2.smx ? "true" : "false");
    fprintf(f, "EIST : %s\n", info->info2.eist ? "true" : "false");
    fprintf(f, "TM2 : %s\n", info->info2.tm2 ? "true" : "false");
    fprintf(f, "SSSE3 : %s\n", info->info2.ssse3 ? "true" : "false");
    fprintf(f, "CNXT-ID : %s\n", info->info2.cnxt_id ? "true" : "false");
    fprintf(f, "FMA : %s\n", info->info2.fma ? "true" : "false");
    fprintf(f, "CX16 : %s\n", info->info2.cx16 ? "true" : "false");
    fprintf(f, "XTPR : %s\n", info->info2.xtpr ? "true" : "false");
    fprintf(f, "PDCM : %s\n", info->info2.pdcm ? "true" : "false");
    fprintf(f, "PCID : %s\n", info->info2.pcid ? "true" : "false");
    fprintf(f, "DCA : %s\n", info->info2.dca ? "true" : "false");
    fprintf(f, "SSE4.1 : %s\n", info->info2.sse41 ? "true" : "false");
    fprintf(f, "SSE4.2 : %s\n", info->info2.sse42 ? "true" : "false");
    fprintf(f, "x2APIC : %s\n", info->info2.x2apic ? "true" : "false");
    fprintf(f, "MOVBE : %s\n", info->info2.movbe ? "true" : "false");
    fprintf(f, "POPCNT : %s\n", info->info2.popcnt ? "true" : "false");
    fprintf(f, "TSC-DEADLINE : %s\n", info->info2.tsc_deadline ? "true" : "false");
    fprintf(f, "AES : %s\n", info->info2.aes ? "true" : "false");
    fprintf(f, "XSAVE : %s\n", info->info2.xsave ? "true" : "false");
    fprintf(f, "OSXSAVE : %s\n", info->info2.osxsave ? "true" : "false");
    fprintf(f, "AVX : %s\n\n", info->info2.avx ? "true" : "false");

    fprintf(f, "FPU : %s\n", info->info2.fpu ? "true" : "false");
    fprintf(f, "VME : %s\n", info->info2.vme ? "true" : "false");
    fprintf(f, "DE : %s\n", info->info2.de ? "true" : "false");
    fprintf(f, "PSE : %s\n", info->info2.pse ? "true" : "false");
    fprintf(f, "TSC : %s\n", info->info2.tsc ? "true" : "false");
    fprintf(f, "MSR : %s\n", info->info2.msr ? "true" : "false");
    fprintf(f, "PAE : %s\n", info->info2.pae ? "true" : "false");
    fprintf(f, "MCE : %s\n", info->info2.mce ? "true" : "false");
    fprintf(f, "CX8 : %s\n", info->info2.cx8 ? "true" : "false");
    fprintf(f, "APIC : %s\n", info->info2.apic ? "true" : "false");
    fprintf(f, "SEP : %s\n", info->info2.sep ? "true" : "false");
    fprintf(f, "MTRR : %s\n", info->info2.mtrr ? "true" : "false");
    fprintf(f, "PGE : %s\n", info->info2.pge ? "true" : "false");
    fprintf(f, "MCA : %s\n", info->info2.mca ? "true" : "false");
    fprintf(f, "CMOV : %s\n", info->info2.cmov ? "true" : "false");
    fprintf(f, "PAT : %s\n", info->info2.pat ? "true" : "false");
    fprintf(f, "PSE-36 : %s\n", info->info2.pse_36 ? "true" : "false");
    fprintf(f, "PSN : %s\n", info->info2.psn ? "true" : "false");
    fprintf(f, "CLFSH : %s\n", info->info2.clfsh ? "true" : "false");
    fprintf(f, "DS : %s\n", info->info2.ds ? "true" : "false");
    fprintf(f, "ACPI : %s\n", info->info2.acpi ? "true" : "false");
    fprintf(f, "MMX : %s\n", info->info2.mmx ? "true" : "false");
    fprintf(f, "FXSR : %s\n", info->info2.fxsr ? "true" : "false");
    fprintf(f, "SSE : %s\n", info->info2.sse ? "true" : "false");
    fprintf(f, "SSE2 : %s\n", info->info2.sse2 ? "true" : "false");
    fprintf(f, "SS : %s\n", info->info2.ss ? "true" : "false");
    fprintf(f, "HTT : %s\n", info->info2.htt ? "true" : "false");
    fprintf(f, "TM : %s\n", info->info2.tm ? "true" : "false");
    fprintf(f, "PBE : %s\n", info->info2.pbe ? "true" : "false");
}
