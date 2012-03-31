#include "get_uname.h"

void get_uname(FILE * f)
{
    struct utsname info;

    if(uname(&info) != 0) {
        fprintf(f, "Fail get Kernel version ...\n");
    } else {
        fprintf(f, "%s %s %s %s %s\n", info.sysname, info.nodename, info.release, info.version, info.machine);
    }
}
