#include "network.h"

#define inaddrr(x) (*(struct in_addr *) &ifr->x[sizeof sa.sin_port])
#define IFRSIZE ((int)(size * sizeof (struct ifreq)))

void interfaces(FILE * f)
{
    unsigned char *u;
    int sockfd, size = 1;
    struct ifreq *ifr;
    struct ifconf ifc;
    struct sockaddr_in sa;


    if(0 > (sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP))) {
        fprintf(f, "Error : cannot open socket\n");
        return;
    }

    ifc.ifc_len = IFRSIZE;
    ifc.ifc_req = NULL;

    do {
        ++size;
        if(NULL == (ifc.ifc_req = realloc(ifc.ifc_req, IFRSIZE))) {
            fprintf(f, "Error : out of memory\n");
            return;
        }
        ifc.ifc_len = IFRSIZE;
        if(ioctl(sockfd, SIOCGIFCONF, &ifc)) {
            fprintf(f, "Error : ioctl SIOCFIFCONF\n");
            return;
        }
    } while(IFRSIZE <= ifc.ifc_len);

    ifr = ifc.ifc_req;
    for (; ifr < ifc.ifc_req + ifc.ifc_len; ++ifr) {

        if(ioctl(sockfd, SIOCGIFFLAGS, ifr)) {
            continue; /* erreur */
        }

        printf("Interface: %s\n", ifr->ifr_name);
        printf("IP Address: %s\n", inet_ntoa(inaddrr(ifr_addr.sa_data)));

        if(!ioctl(sockfd, SIOCGIFHWADDR, ifr)) {
            if(ifr->ifr_hwaddr.sa_family == ARPHRD_ETHER){
                u = (unsigned char *) &ifr->ifr_addr.sa_data;

                if(u[0] + u[1] + u[2] + u[3] + u[4] + u[5])
                    printf("HW Address: %2.2x.%2.2x.%2.2x.%2.2x.%2.2x.%2.2x\n", u[0], u[1], u[2], u[3], u[4], u[5]);

                if(!ioctl(sockfd, SIOCGIFNETMASK, ifr))
                    printf("Netmask: %s\n", inet_ntoa(inaddrr(ifr_addr.sa_data)));

                if(ifr->ifr_flags & IFF_BROADCAST)
                    if(!ioctl(sockfd, SIOCGIFBRDADDR, ifr))
                        printf("Broadcast: %s\n", inet_ntoa(inaddrr(ifr_addr.sa_data)));

                if(!ioctl(sockfd, SIOCGIFMTU, ifr))
                    printf("MTU: %u\n", ifr->ifr_mtu);

                if(!ioctl(sockfd, SIOCGIFMETRIC, ifr))
                    printf("Metric: %u\n", ifr->ifr_metric);
            }
        }
        printf("\n");
    }
    close(sockfd);

    return;
}
