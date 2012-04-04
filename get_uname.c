#include "get_uname.h"

void get_uname(FILE * f, char html)
{
    struct utsname info;

    if(uname(&info) != 0) {
        print(f, html, "Fail get Kernel version ...");
    } else {
        print(f, html, "%s %s %s %s %s", info.sysname, info.nodename, info.release, info.version, info.machine);
    }
}
