#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <iostream>
#include <string>

class Socket
{
    int32_t sock_fd;
    struct sockaddr_in servername;

    public:

        Socket(uint32_t port) 
        {
            // init file descriptor
            sock_fd = socket(PF_INET, SOCK_STREAM, 0);

            // file descriptor fail
            if (sock_fd < 0) {
                printf("err\n");
                return;
            }

            servername.sin_family = AF_INET;
            servername.sin_port = htons(port);
        };

        bool Connect(const char *hostname) {
            
            struct hostent *hostinfo = gethostbyname(hostname);
            
            // host not found
            if (hostinfo == NULL) {
                return false;
            }

            servername.sin_addr = *(struct in_addr *) hostinfo->h_addr;

            if (0 > connect(sock_fd, (struct sockaddr *)&servername, sizeof(servername))) {
                return false;
            }
            return true;
        }

        bool Close() { close(sock_fd); }

        int Write(std::string value)
        {
            int nbytes = ::write(sock_fd, value.c_str(), strlen(value.c_str()) + 1);
            if (nbytes < 0) {
                return 0;
            }
            
            return nbytes;
        }

        const std::string Read() {
            char buffer[512];
            int nbytes;

            memset(buffer, 0x00, 512);

            nbytes = ::read(sock_fd, buffer, 512);
            if (nbytes < 0) {
                printf("no bytes read\n");
            }
            else if (nbytes == 0) {
                printf("EOF\n");
            }
            else {
                if (buffer != NULL)
                    return std::string(buffer);
                return "";
            }
        }
};
