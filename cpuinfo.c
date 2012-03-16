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

void getProcessorInfo(EAX1 * res)
{
    unsigned int e[4];
    unsigned char tmp;
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
    tmp = (e[0] >> 0xC) & 0x3; /* 12-13 */
    res->extendedmodel = (e[0] >> 0x10) & 0x7; /* 16-19 */
    res->extendedfamily = (e[0] >> 0x14) & 0xFF; /* 20-27 */

    switch(tmp){
        case 0: 
            res->cputype = "Original OEM Processor (0x0)\n";
            break;
        case 1:
            res->cputype = "OverDrive Processor (0x1)\n";
            break;
        case 2:
            res->cputype = "Dual Processor (0x2)\n";
            break;
        default:
            res->cputype = "Unknown\n";
    }

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
    unsigned char tmp;
    asm("cpuid"
        : "=a" (e[0]),
        "=b" (e[1]),
        "=c" (e[2]),
        "=d" (e[3])
        : "a" (2)
        );

    nb = e[0] & 0xFF;
    printf("nb => 0x%x\n", nb);
    for(i=1; i < 16; ++i) {
        if(i < 4)
            tmp = (e[0] >> 0x8*i) & 0xFF;
        else if(i < 8)
            tmp = (e[1] >> 0x8*(i%4)) & 0xFF;
        else if(i < 12)
            tmp = (e[2] >> 0x8*(i%4)) & 0xFF;
        else
            tmp = (e[3] >> 0x8*(i%4)) & 0xFF;
        switch(tmp){
            case 0x01:
                res->caches[i-1] = "Instruction TLB: 4-KB Pages, 4-way set associative, 32 entries";
                break;
            case 0x02:
                res->caches[i-1] = "Instruction TLB: 4-MB Pages, fully associative, 2 entries";
                break;
            case 0x03:
                res->caches[i-1] = "Data TLB: 4-KB Pages, 4-way set associative, 64 entries";
                break;
            case 0x04:
                res->caches[i-1] = "Data TLB: 4-MB Pages, 4-way set associative, 8 entries";
                break;
            case 0x05:
                res->caches[i-1] = "Data TLB: 4-MB Pages, 4-way set associative, 32 entries";
                break;
            case 0x06:
                res->caches[i-1] = "1st-level instruction cache: 8-KB, 4-way set associative, 32-byte line size";
                break;
            case 0x08:
                res->caches[i-1] = "1st-level instruction cache: 16-KB, 4-way set associative, 32-byte line size";
                break;
            case 0x09:
                res->caches[i-1] = "1st-level Instruction Cache: 32-KB, 4-way set associative, 64-byte line size";
                break;
            case 0x0A:
                res->caches[i-1] = "1st-level data cache: 8-KB, 2-way set associative, 32-byte line size";
                break;
            case 0x0B:
                res->caches[i-1] = "Instruction TLB: 4-MB pages, 4-way set associative, 4 entries";
                break;
            case 0x0C:
                res->caches[i-1] = "1st-level data cache: 16-KB, 4-way set associative, 32-byte line size";
                break;
            case 0x0D:
                res->caches[i-1] = "1st-level Data Cache: 16-KB, 4-way set associative, 64-byte line size, ECC";
                break;
            case 0x0E:
                res->caches[i-1] = "1st-level Data Cache: 24-KB, 6-way set associative, 64-byte line size, ECC";
                break;
            case 0x21:
                res->caches[i-1] = "2nd-level cache: 256-KB, 8-way set associative, 64-byte line size";
                break;
            case 0x22:
                res->caches[i-1] = "3rd-level cache: 512-KB, 4-way set associative, sectored cache, 64-byte line size";
                break;
            case 0x23:
                res->caches[i-1] = "3rd-level cache: 1-MB, 8-way set associative, sectored cache, 64-byte line size";
                break;
            case 0x25:
                res->caches[i-1] = "3rd-level cache: 2-MB, 8-way set associative, sectored cache, 64-byte line size";
                break;
            case 0x29:
                res->caches[i-1] = "3rd-level cache: 4-MB, 8-way set associative, sectored cache, 64-byte line size";
                break;
            case 0x2C:
                res->caches[i-1] = "1st-level data cache: 32-KB, 8-way set associative, 64-byte line size";
                break;
            case 0x30:
                res->caches[i-1] = "1st-level instruction cache: 32-KB, 8-way set associative, 64-byte line size";
                break;
            case 0x40:
                res->caches[i-1] = "No 2nd-level cache or, if processor contains a valid 2nd-level cache, no 3rd-level cache";
                break;
            case 0x41:
                res->caches[i-1] = "2nd-level cache: 128-KB, 4-way set associative, 32-byte line size";
                break;
            case 0x42:
                res->caches[i-1] = "2nd-level cache: 256-KB, 4-way set associative, 32-byte line size";
                break;
            case 0x43:
                res->caches[i-1] = "2nd-level cache: 512-KB, 4-way set associative, 32-byte line size";
                break;
            case 0x44:
                res->caches[i-1] = "2nd-level cache: 1-MB, 4-way set associative, 32-byte line size";
                break;
            case 0x45:
                res->caches[i-1] = "2nd-level cache: 2-MB, 4-way set associative, 32-byte line size";
                break;
            case 0x46:
                res->caches[i-1] = "3rd-level cache: 4-MB, 4-way set associative, 64-byte line size";
                break;
            case 0x47:
                res->caches[i-1] = "3rd-level cache: 8-MB, 8-way set associative, 64-byte line size";
                break;
            case 0x48:
                res->caches[i-1] = "2nd-level cache: 3-MB, 12-way set associative, 64-byte line size, unified on-die";
                break;
            case 0x49:
                res->caches[i-1] = "3rd-level cache: 4-MB, 16-way set associative, 64-byte line size (Intel Xeon processor MP, Family 0Fh, Model 06h) 2nd-level cache: 4-MB, 16-way set associative, 64-byte line size";
                break;
            case 0x4A:
                res->caches[i-1] = "3rd-level cache: 6-MB, 12-way set associative, 64-byte line size";
            case 0x4B:
                res->caches[i-1] = "3rd-level cache: 8-MB, 16-way set associative, 64-byte line size";
                break;
            case 0x4C:
                res->caches[i-1] = "3rd-level cache: 12-MB, 12-way set associative, 64-byte line size";
                break;
            case 0x4D:
                res->caches[i-1] = "3rd-level cache: 16-MB, 16-way set associative, 64-byte line size";
                break;
            case 0x4E:
                res->caches[i-1] = "2nd-level cache: 6-MB, 24-way set associative, 64-byte line size";
                break;
            case 0x4F:
                res->caches[i-1] = "Instruction TLB: 4-KB pages, 32 entries";
                break;
            case 0x50:
                res->caches[i-1] = "Instruction TLB: 4-KB, 2-MB or 4-MB pages, fully associative, 64 entries";
                break;
            case 0x51:
                res->caches[i-1] = "Instruction TLB: 4-KB, 2-MB or 4-MB pages, fully associative, 128 entries";
                break;
            case 0x52:
                res->caches[i-1] = "Instruction TLB: 4-KB, 2-MB or 4-MB pages, fully associative, 256 entries";
                break;
            case 0x55:
                res->caches[i-1] = "Instruction TLB: 2-MB or 4-MB pages, fully associative, 7 entries";
                break;
            case 0x56:
                res->caches[i-1] = "L1 Data TLB: 4-MB pages, 4-way set associative, 16 entries";
                break;
            case 0x57:
                res->caches[i-1] = "L1 Data TLB: 4-KB pages, 4-way set associative, 16 entries";
                break;
            case 0x59:
                res->caches[i-1] = "Data TLB0: 4-KB pages, fully associative, 16 entries";
                break;
            case 0x5A:
                res->caches[i-1] = "Data TLB0: 2-MB or 4-MB pages, 4-way associative, 32 entries";
                break;
            case 0x5B:
                res->caches[i-1] = "Data TLB: 4-KB or 4-MB pages, fully associative, 64 entries";
                break;
            case 0x5C:
                res->caches[i-1] = "Data TLB: 4-KB or 4-MB pages, fully associative, 128 entries";
                break;
            case 0x5D:
                res->caches[i-1] = "Data TLB: 4-KB or 4-MB pages, fully associative, 256 entries";
                break;
            case 0x60:
                res->caches[i-1] = "1st-level data cache: 16-KB, 8-way set associative, sectored cache, 64-byte line size";
                break;
            case 0x66:
                res->caches[i-1] = "1st-level data cache: 8-KB, 4-way set associative, sectored cache, 64-byte line size";
                break;
            case 0x67:
                res->caches[i-1] = "1st-level data cache: 16-KB, 4-way set associative, sectored cache, 64-byte line size";
                break;
            case 0x68:
                res->caches[i-1] = "1st-level data cache: 32-KB, 4 way set associative, sectored cache, 64-byte line size";
                break;
            case 0x70:
                res->caches[i-1] = "Trace cache: 12K-uops, 8-way set associative";
                break;
            case 0x71:
                res->caches[i-1] = "Trace cache: 16K-uops, 8-way set associative";
                break;
            case 0x72:
                res->caches[i-1] = "Trace cache: 32K-uops, 8-way set associative";
                break;
            case 0x76:
                res->caches[i-1] = "2nd-level cache: 1-MB, 4-way set associative, 64-byte line size";
                break;
            case 0x78:
                res->caches[i-1] = "2nd-level cache: 1-MB, 4-way set associative, 64-byte line size";
                break;
            case 0x79:
                res->caches[i-1] = "2nd-level cache: 128-KB, 8-way set associative, sectored cache, 64-byte line size";
                break;
            case 0x7A:
                res->caches[i-1] = "2nd-level cache: 256-KB, 8-way set associative, sectored cache, 64-byte line size";
                break;
            case 0x7B:
                res->caches[i-1] = "2nd-level cache: 512-KB, 8-way set associative, sectored cache, 64-byte line size";
                break;
            case 0x7C:
                res->caches[i-1] = "2nd-level cache: 1-MB, 8-way set associative, sectored cache, 64-byte line size";
                break;
            case 0x7D:
                res->caches[i-1] = "2nd-level cache: 2-MB, 8-way set associative, 64-byte line size";
                break;
            case 0x7F:
                res->caches[i-1] = "2nd-level cache: 512-KB, 2-way set associative, 64-byte line size";
                break;
            case 0x80:
                res->caches[i-1] = "2nd-level cache: 512-KB, 8-way set associative, 64-byte line size";
                break;
            case 0x82:
                res->caches[i-1] = "2nd-level cache: 256-KB, 8-way set associative, 32-byte line size";
                break;
            case 0x83:
                res->caches[i-1] = "2nd-level cache: 512-KB, 8-way set associative, 32-byte line size";
                break;
            case 0x84:
                res->caches[i-1] = "2nd-level cache: 1-MB, 8-way set associative, 32-byte line size";
                break;
            case 0x85:
                res->caches[i-1] = "2nd-level cache: 2-MB, 8-way set associative, 32-byte line size";
                break;
            case 0x86:
                res->caches[i-1] = "2nd-level cache: 512-KB, 4-way set associative, 64-byte line size";
                break;
            case 0x87:
                res->caches[i-1] = "2nd-level cache: 1-MB, 8-way set associative, 64-byte line size";
                break;
            case 0xB0:
                res->caches[i-1] = "Instruction TLB: 4-KB Pages, 4-way set associative, 128 entries";
                break;
            case 0xB1:
                res->caches[i-1] = "Instruction TLB: 2-MB pages, 4-way, 8 entries or 4M pages, 4-way, 4 entries";
                break;
            case 0xB2:
                res->caches[i-1] = "Instruction TLB: 4-KB pages, 4-way set associative, 64 entries";
                break;
            case 0xB3:
                res->caches[i-1] = "Data TLB: 4-KB Pages, 4-way set associative, 128 entries";
                break;
            case 0xB4:
                res->caches[i-1] = "Data TLB: 4-KB Pages, 4-way set associative, 256 entries";
                break;
            case 0xBA:
                res->caches[i-1] = "Data TLB: 4-KB Pages, 4-way set associative, 64 entries";
                break;
            case 0xC0:
                res->caches[i-1] = "Data TLB: 4-KB or 4-MB Pages, 4-way set associative, 8 entries";
                break;
            case 0xCA:
                res->caches[i-1] = "Shared 2nd-level TLB: 4 KB pages, 4-way set associative, 512 entries";
                break;
            case 0xD0:
                res->caches[i-1] = "3rd-level cache: 512-kB, 4-way set associative, 64-byte line size";
                break;
            case 0xD1:
                res->caches[i-1] = "3rd-level cache: 1-MB, 4-way set associative, 64-byte line size";
                break;
            case 0xD2:
                res->caches[i-1] = "3rd-level cache: 2-MB, 4-way set associative, 64-byte line size";
                break;
            case 0xD6:
                res->caches[i-1] = "3rd-level cache: 1-MB, 8-way set associative, 64-byte line size";
                break;
            case 0xD7:
                res->caches[i-1] = "3rd-level cache: 2-MB, 8-way set associative, 64-byte line size";
                break;
            case 0xD8:
                res->caches[i-1] = "3rd-level cache: 4-MB, 8-way set associative, 64-byte line size";
                break;
            case 0xDC:
                res->caches[i-1] = "3rd-level cache: 1.5-MB, 12-way set associative, 64-byte line size";
                break;
            case 0xDD:
                res->caches[i-1] = "3rd-level cache: 3-MB, 12-way set associative, 64-byte line size";
                break;
            case 0xDE:
                res->caches[i-1] = "3rd-level cache: 6-MB, 12-way set associative, 64-byte line size";
                break;
            case 0xE2:
                res->caches[i-1] = "3rd-level cache: 2-MB, 16-way set associative, 64-byte line size";
                break;
            case 0xE3:
                res->caches[i-1] = "3rd-level cache: 4-MB, 16-way set associative, 64-byte line size";
                break;
            case 0xE4:
                res->caches[i-1] = "3rd-level cache: 8-MB, 16-way set associative, 64-byte line size";
                break;
            case 0xEA:
                res->caches[i-1] = "3rd-level cache: 12-MB, 24-way set associative, 64-byte line size";
                break;
            case 0xEB:
                res->caches[i-1] = "3rd-level cache: 18-MB, 24-way set associative, 64-byte line size";
                break;
            case 0xEC:
                res->caches[i-1] = "3rd-level cache: 24-MB, 24-way set associative, 64-byte line size";
                break;
            case 0xF0:
                res->caches[i-1] = "64-byte Prefetching";
                break;
            case 0xF1:
                res->caches[i-1] = "128-byte Prefetching";
                break;
            case 0xFF:
                res->caches[i-1] = "CPUID Leaf 2 does not report cache descriptor information; use CPUID Leaf 4 to query cache parameters";
                break;
            default:
                res->caches[i-1] = NULL;
        }
    }
}

void getCachesParameters(EAX4 * res)
{
    int i = 0;
    char tmp;
    EAX4 * current = res;
    unsigned int e[4];
    do {
        asm("cpuid"
            : "=a" (e[0]),
            "=b" (e[1]),
            "=c" (e[2]),
            "=d" (e[3])
            : "a" (4),
            "c" (i)
           );
        tmp = e[0] & 0x1F;
        if(tmp > 0) {
            if(i) {
                current->next = malloc(sizeof(EAX4));
                current = current->next;
            }
            switch(tmp) {
                case 0:
                    current->cache_type = "NULL (0)"; break;
                case 1:
                    current->cache_type = "Data Cache (1)"; break;
                case 2:
                    current->cache_type = "Instruction Cache (2)"; break;
                case 3:
                    current->cache_type = "Unified Cache (3)"; break;
            }
            current->cache_level = (e[0] >> 5) & 0x7;
            current->sicl = (e[0] >> 8) & 0x1;
            current->fac = (e[0] >> 9) & 0x1;
            current->mntstc = (e[0] >> 14) & 0x7FF;
            current->napicidrtp = (e[0] >> 26) & 0x1F;

            current->scls = e[1] & 0xFFF;
            current->plp = (e[1] >> 12) & 0x3FF;
            current->woa = (e[1] >> 22) & 0x3FF;

            current->nsets = e[2];

            current->wbinvd = e[3] & 0x1;
            current->ciitlcl = (e[3] >> 1) & 0x1;
            current->cci = (e[3] >> 2) & 0x1;

            current->cache_size = (current->woa + 1) * (current->plp + 1) * (current->scls + 1);

            i += 1;
        }
    } while(tmp != 0);
}

CPUID_INFO CPUID_INFO_create()
{
    CPUID_INFO res = malloc(sizeof(struct cpuid_info));
    getVendor(&(res->info1));
    getProcessorInfo(&(res->info2));
    getCachesInfo(&(res->info3));
    getCachesParameters(&(res->info4));
    return res;
}

void CPUID_INFO_free(CPUID_INFO p)
{
    EAX4 * a = p->info4.next, * b;
    while(a != NULL)
    {
        b = a;
        a = a->next;
        free(b);
    }
    free(p);
}

void CPUID_INFO_fprintf(FILE * f, CPUID_INFO info)
{
    int i;
    EAX4 * current;
    fprintf(f, "Largest Standard Function Number Supported : 0x%x\n", info->info1.lsfns);
    fprintf(f, "Vendor                                     : %s\n\n", info->info1.vendor);
    fprintf(f, "Stepping                                   : 0x%x\n", info->info2.stepping);
    fprintf(f, "Model                                      : 0x%x\n", info->info2.model);
    fprintf(f, "Family                                     : 0x%x\n", info->info2.family);
    fprintf(f, "Processor type                             : %s\n", info->info2.cputype);
    fprintf(f, "Extended model                             : 0x%x\n", info->info2.extendedmodel);
    fprintf(f, "Extended family                            : 0x%x\n\n", info->info2.extendedfamily);

    fprintf(f, "Brand ID                : 0x%x\n", info->info2.brand_id);
    fprintf(f, "Chunks                  : 0x%x\n", info->info2.chunks);
    fprintf(f, "Logical Processor Count : 0x%x (%d)\n", info->info2.count, info->info2.count);
    fprintf(f, "APIC ID                 : 0x%x\n\n", info->info2.apic_id);

    fprintf(f, "SSE3         : %s\n", info->info2.sse3 ? "true" : "false");
    fprintf(f, "PCLMULDQ     : %s\n", info->info2.pclmuldq ? "true" : "false");
    fprintf(f, "DTES64       : %s\n", info->info2.dtes64 ? "true" : "false");
    fprintf(f, "MONITOR      : %s\n", info->info2.monitor ? "true" : "false");
    fprintf(f, "DS-CPL       : %s\n", info->info2.ds_cpl ? "true" : "false");
    fprintf(f, "VMX          : %s\n", info->info2.vmx ? "true" : "false");
    fprintf(f, "SMX          : %s\n", info->info2.smx ? "true" : "false");
    fprintf(f, "EIST         : %s\n", info->info2.eist ? "true" : "false");
    fprintf(f, "TM2          : %s\n", info->info2.tm2 ? "true" : "false");
    fprintf(f, "SSSE3        : %s\n", info->info2.ssse3 ? "true" : "false");
    fprintf(f, "CNXT-ID      : %s\n", info->info2.cnxt_id ? "true" : "false");
    fprintf(f, "FMA          : %s\n", info->info2.fma ? "true" : "false");
    fprintf(f, "CX16         : %s\n", info->info2.cx16 ? "true" : "false");
    fprintf(f, "XTPR         : %s\n", info->info2.xtpr ? "true" : "false");
    fprintf(f, "PDCM         : %s\n", info->info2.pdcm ? "true" : "false");
    fprintf(f, "PCID         : %s\n", info->info2.pcid ? "true" : "false");
    fprintf(f, "DCA          : %s\n", info->info2.dca ? "true" : "false");
    fprintf(f, "SSE4.1       : %s\n", info->info2.sse41 ? "true" : "false");
    fprintf(f, "SSE4.2       : %s\n", info->info2.sse42 ? "true" : "false");
    fprintf(f, "x2APIC       : %s\n", info->info2.x2apic ? "true" : "false");
    fprintf(f, "MOVBE        : %s\n", info->info2.movbe ? "true" : "false");
    fprintf(f, "POPCNT       : %s\n", info->info2.popcnt ? "true" : "false");
    fprintf(f, "TSC-DEADLINE : %s\n", info->info2.tsc_deadline ? "true" : "false");
    fprintf(f, "AES          : %s\n", info->info2.aes ? "true" : "false");
    fprintf(f, "XSAVE        : %s\n", info->info2.xsave ? "true" : "false");
    fprintf(f, "OSXSAVE      : %s\n", info->info2.osxsave ? "true" : "false");
    fprintf(f, "AVX          : %s\n\n", info->info2.avx ? "true" : "false");

    fprintf(f, "FPU          : %s\n", info->info2.fpu ? "true" : "false");
    fprintf(f, "VME          : %s\n", info->info2.vme ? "true" : "false");
    fprintf(f, "DE           : %s\n", info->info2.de ? "true" : "false");
    fprintf(f, "PSE          : %s\n", info->info2.pse ? "true" : "false");
    fprintf(f, "TSC          : %s\n", info->info2.tsc ? "true" : "false");
    fprintf(f, "MSR          : %s\n", info->info2.msr ? "true" : "false");
    fprintf(f, "PAE          : %s\n", info->info2.pae ? "true" : "false");
    fprintf(f, "MCE          : %s\n", info->info2.mce ? "true" : "false");
    fprintf(f, "CX8          : %s\n", info->info2.cx8 ? "true" : "false");
    fprintf(f, "APIC         : %s\n", info->info2.apic ? "true" : "false");
    fprintf(f, "SEP          : %s\n", info->info2.sep ? "true" : "false");
    fprintf(f, "MTRR         : %s\n", info->info2.mtrr ? "true" : "false");
    fprintf(f, "PGE          : %s\n", info->info2.pge ? "true" : "false");
    fprintf(f, "MCA          : %s\n", info->info2.mca ? "true" : "false");
    fprintf(f, "CMOV         : %s\n", info->info2.cmov ? "true" : "false");
    fprintf(f, "PAT          : %s\n", info->info2.pat ? "true" : "false");
    fprintf(f, "PSE-36       : %s\n", info->info2.pse_36 ? "true" : "false");
    fprintf(f, "PSN          : %s\n", info->info2.psn ? "true" : "false");
    fprintf(f, "CLFSH        : %s\n", info->info2.clfsh ? "true" : "false");
    fprintf(f, "DS           : %s\n", info->info2.ds ? "true" : "false");
    fprintf(f, "ACPI         : %s\n", info->info2.acpi ? "true" : "false");
    fprintf(f, "MMX          : %s\n", info->info2.mmx ? "true" : "false");
    fprintf(f, "FXSR         : %s\n", info->info2.fxsr ? "true" : "false");
    fprintf(f, "SSE          : %s\n", info->info2.sse ? "true" : "false");
    fprintf(f, "SSE2         : %s\n", info->info2.sse2 ? "true" : "false");
    fprintf(f, "SS           : %s\n", info->info2.ss ? "true" : "false");
    fprintf(f, "HTT          : %s\n", info->info2.htt ? "true" : "false");
    fprintf(f, "TM           : %s\n", info->info2.tm ? "true" : "false");
    fprintf(f, "PBE          : %s\n", info->info2.pbe ? "true" : "false");

    fprintf(f, "\nCaches and TLB descriptor :\n");
    for(i=0; i < 15; ++i)
        if(info->info3.caches[i])
            fprintf(f, "     %s\n", info->info3.caches[i]);

    current = &(info->info4);
    i = 0;
    fprintf(f, "\n");
    while(current != NULL) {
        fprintf(f, " ------ Cache : %d ------\n", i);
        fprintf(f, "Cache type                                   : %s\n", current->cache_type);
        fprintf(f, "Cache level                                  : 0x%x\n", current->cache_level);
        fprintf(f, "Cache size                                   : %d bytes\n", current->cache_size);
        fprintf(f, "Self initializing cache level                : %s\n", current->sicl ? "true" : "false");
        fprintf(f, "Fully associative cache                      : %s\n", current->fac ? "true" : "false");
        fprintf(f, "Maximum number of threads sharing this cache : %d\n", current->mntstc);
        fprintf(f, "Number of APIC IDs reserved for this package : %d\n", current->napicidrtp);
        fprintf(f, "System Coherency Line Size                   : %d\n", current->scls);
        fprintf(f, "Physical Line partitions                     : %d\n", current->plp);
        fprintf(f, "Ways of Associativity                        : %d\n", current->woa);
        fprintf(f, "Number of Sets  - 1                          : %d\n", current->nsets);
        fprintf(f, "WBINVD/INVD behavior on lower level caches   : %s\n", current->wbinvd ? "true" : "false");
        fprintf(f, "Cache is inclusive to lower cache levels     : %s\n", current->ciitlcl ? "true" : "false");
        fprintf(f, "Complex Cache Indexing                       : %s\n", current->cci ? "true" : "false");
        current = current->next;
        ++i;
    }
}
