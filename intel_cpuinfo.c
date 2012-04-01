#include "intel_cpuinfo.h"

void intel_getProcessorInfo(intel_EAX1 * res)
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

void intel_getCachesInfo(intel_EAX2 * res)
{
    unsigned int e[4];
    int i;
    unsigned char tmp;
    asm("cpuid"
        : "=a" (e[0]),
        "=b" (e[1]),
        "=c" (e[2]),
        "=d" (e[3])
        : "a" (2)
        );

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

void intel_getCachesParameters(intel_EAX4 * res)
{
    int i = 0;
    char tmp;
    intel_EAX4 * current = res;
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
                current->next = malloc(sizeof(intel_EAX4));
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
                default:
                    current->cache_type = "Unknown Cache type"; break;
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

            current->cache_size = (current->woa + 1) * (current->plp + 1) * (current->scls + 1) * (current->nsets + 1);

            i += 1;
        }
    } while(tmp != 0);
}

void intel_getProcessorTopology(intel_EAXB * res)
{
    unsigned int e[4];

    asm("cpuid"
        : "=a" (e[0]),
        "=b" (e[1]),
        "=c" (e[2]),
        "=d" (e[3])
        : "a" (0x0B),
        "c" (0)
       );

    res->thread_apic_id = e[0] & 0x1F;
    res->thread_cpu = e[1] & 0xFFFF;
    res->thread_level_number = e[2] & 0xFF;
    res->thread_level_type = (e[2] >> 8) & 0xFF;
    res->thread_extended_apic = e[3];

    asm("cpuid"
        : "=a" (e[0]),
        "=b" (e[1]),
        "=c" (e[2]),
        "=d" (e[3])
        : "a" (0x0B),
        "c" (1)
       );

    res->core_apic_id = e[0] & 0x1F;
    res->core_cpu = e[1] & 0xFFFF;
    res->core_level_number = e[2] & 0xFF;
    res->core_level_type = (e[2] >> 8) & 0xFF;
    res->core_extended_apic = e[3];
}

void intel_CPUID_INFO2_free(intel_EAX1 * res) {}

void intel_CPUID_INFO3_free(intel_EAX2 * res) {}

void intel_CPUID_INFO4_free(intel_EAX4 * res)
{
    intel_EAX4 * a = res->next, * b;
    while(a != NULL)
    {
        b = a;
        a = a->next;
        free(b);
    }
}

void intel_CPUID_INFO5_free(intel_EAXB * res) {}

void intel_CPUID_INFO2_fprintf(FILE * f, intel_EAX1 * info2)
{
    int a = 0;

    fprintf(f, "Processor Brand String                     : %s\n", info2->cpuname);
    fprintf(f, "Stepping                                   : 0x%x\n", info2->stepping);
    fprintf(f, "Model                                      : 0x%x\n", info2->model);
    fprintf(f, "Family                                     : 0x%x\n", info2->family);
    fprintf(f, "Processor type                             : %s\n", info2->cputype);
    fprintf(f, "Extended model                             : 0x%x\n", info2->extendedmodel);
    fprintf(f, "Extended family                            : 0x%x\n\n", info2->extendedfamily);

    fprintf(f, "Brand ID                : 0x%x\n", info2->brand_id);
    fprintf(f, "Chunks                  : 0x%x\n", info2->chunks);
    fprintf(f, "Logical Processor Count : 0x%x (%d)\n", info2->count, info2->count);
    fprintf(f, "APIC ID                 : 0x%x\n\n", info2->apic_id);

    fprintf(f, "Features supported :\n");

    if(info2->sse3){ fprintf(f, "SSE3 "); ++a; }
    if(info2->pclmuldq){ fprintf(f, "PCLMULDQ "); ++a; }
    if(info2->dtes64){ fprintf(f, "DTES64 "); ++a; }
    if(info2->monitor){ fprintf(f, "MONITOR "); ++a; }
    if(info2->ds_cpl){ fprintf(f, "DS-CPL "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->vmx){ fprintf(f, "VMX "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->smx){ fprintf(f, "SMX "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->eist){ fprintf(f, "EIST "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->tm2){ fprintf(f, "TM2 "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->ssse3){ fprintf(f, "SSSE3 "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->cnxt_id){ fprintf(f, "CNXT-ID "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->fma){ fprintf(f, "FMA "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->cx16){ fprintf(f, "CX16 "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->xtpr){ fprintf(f, "XTPR "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->pdcm){ fprintf(f, "PDCM "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->pcid){ fprintf(f, "PCID "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->dca){ fprintf(f, "DCA "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->sse41){ fprintf(f, "SSE4.1 "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->sse42){ fprintf(f, "SSE4.2 "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->x2apic){ fprintf(f, "x2APIC "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->movbe){ fprintf(f, "MOVBE "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->popcnt){ fprintf(f, "POPCNT "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->tsc_deadline){ fprintf(f, "TSC-DEADLINE "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->aes){ fprintf(f, "AES "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->xsave){ fprintf(f, "XSAVE "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->osxsave){ fprintf(f, "OSXSAVE "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->avx){ fprintf(f, "AVX "); ++a; }
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
    if(info2->psn){ fprintf(f, "PSN "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->clfsh){ fprintf(f, "CLFSH "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->ds){ fprintf(f, "DS "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->acpi){ fprintf(f, "ACPI "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->mmx){ fprintf(f, "MMX "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->fxsr){ fprintf(f, "FXSR "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->sse){ fprintf(f, "SSE "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->sse2){ fprintf(f, "SSE2 "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->ss){ fprintf(f, "SS "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->htt){ fprintf(f, "HTT "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->tm){ fprintf(f, "TM "); ++a; }
    if(a >= 5){ fprintf(f, "\n"); a = 0; }
    if(info2->pbe){ fprintf(f, "PBE "); ++a; }
    fprintf(f, "\n");
}

void intel_CPUID_INFO3_fprintf(FILE * f, intel_EAX2 * info3)
{
    int i;
    fprintf(f, "\nCaches and TLB descriptor :\n");
    for(i=0; i < 15; ++i)
        if(info3->caches[i])
            fprintf(f, "     %s\n", info3->caches[i]);
}

void intel_CPUID_INFO4_fprintf(FILE * f, intel_EAX4 * info4)
{
    int i=0;
    intel_EAX4 * current = info4;
    fprintf(f, "\n");
    while(current != NULL) {
        fprintf(f, " ------ Cache level : %d ------\n", current->cache_level);
        fprintf(f, "Cache type                                   : %s\n", current->cache_type);
        fprintf(f, "Cache level                                  : 0x%x\n", current->cache_level);
        fprintf(f, "Cache size                                   : %dK\n", current->cache_size/1024);
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
        fprintf(f, "Complex Cache Indexing                       : %s\n\n", current->cci ? "true" : "false");
        current = current->next;
        ++i;
    }
}

void intel_CPUID_INFO5_fprintf(FILE * f, intel_EAXB * info5)
{
    fprintf(f, "\n ------ Thread Level Processor Topology ------\n");
    fprintf(f, "bits to shift APIC ID to get next                             : 0x%x\n", info5->thread_apic_id);
    fprintf(f, "Number of factory-configured logical processors at this level : 0x%x\n", info5->thread_cpu);
    fprintf(f, "Level type                                                    : 0x%x\n", info5->thread_level_type);
    fprintf(f, "Level number                                                  : 0x%x\n", info5->thread_level_number);
    fprintf(f, "Extended APIC ID                                              : 0x%x\n", info5->thread_extended_apic);
    fprintf(f, "\n ------ Core Level Processor Topology ------\n");
    fprintf(f, "bits to shift APIC ID to get next                             : 0x%x\n", info5->core_apic_id);
    fprintf(f, "Number of factory-configured logical processors at this level : 0x%x\n", info5->core_cpu);
    fprintf(f, "Level type                                                    : 0x%x\n", info5->core_level_type);
    fprintf(f, "Level number                                                  : 0x%x\n", info5->core_level_number);
    fprintf(f, "Extended APIC ID                                              : 0x%x\n", info5->core_extended_apic);
}
