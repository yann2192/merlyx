#include "network.h"

#define inaddrr(x) (*(struct in_addr *) &ifr->x[sizeof sa.sin_port])
#define IFRSIZE ((int)(size * sizeof (struct ifreq)))

void interfaces(FILE * f, char html)
{
    unsigned char *u;
    int sockfd, size = 1;
    struct ifreq *ifr;
    struct ifconf ifc;
    struct sockaddr_in sa;


    if(0 > (sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP))) {
        print(f, html, "Error : cannot open socket");
        return;
    }

    ifc.ifc_len = IFRSIZE;
    ifc.ifc_req = NULL;

    do {
        ++size;
        if(NULL == (ifc.ifc_req = realloc(ifc.ifc_req, IFRSIZE))) {
            print(f, html, "Error : out of memory");
            return;
        }
        ifc.ifc_len = IFRSIZE;
        if(ioctl(sockfd, SIOCGIFCONF, &ifc)) {
            print(f, html, "Error : ioctl SIOCFIFCONF");
            return;
        }
    } while(IFRSIZE <= ifc.ifc_len);

    ifr = ifc.ifc_req;
    for (; ifr < ifc.ifc_req + ifc.ifc_len; ++ifr) {

        if(ioctl(sockfd, SIOCGIFFLAGS, ifr)) {
            continue; /* erreur */
        }

        print(f, html, "Interface: %s", ifr->ifr_name);
        print(f, html, "IP Address: %s", inet_ntoa(inaddrr(ifr_addr.sa_data)));

        if(!ioctl(sockfd, SIOCGIFHWADDR, ifr)) {
            if(ifr->ifr_hwaddr.sa_family == ARPHRD_ETHER){
                u = (unsigned char *) &ifr->ifr_addr.sa_data;

                if(u[0] + u[1] + u[2] + u[3] + u[4] + u[5])
                    print(f, html, "HW Address: %2.2x.%2.2x.%2.2x.%2.2x.%2.2x.%2.2x", u[0], u[1], u[2], u[3], u[4], u[5]);

                if(!ioctl(sockfd, SIOCGIFNETMASK, ifr))
                    print(f, html, "Netmask: %s", inet_ntoa(inaddrr(ifr_addr.sa_data)));

                if(ifr->ifr_flags & IFF_BROADCAST)
                    if(!ioctl(sockfd, SIOCGIFBRDADDR, ifr))
                        print(f, html, "Broadcast: %s", inet_ntoa(inaddrr(ifr_addr.sa_data)));

                if(!ioctl(sockfd, SIOCGIFMTU, ifr))
                    print(f, html, "MTU: %u", ifr->ifr_mtu);

                if(!ioctl(sockfd, SIOCGIFMETRIC, ifr))
                    print(f, html, "Metric: %u", ifr->ifr_metric);
            }
        }
        print_nl(f, html);
    }
    close(sockfd);

    return;
}
