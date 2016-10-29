#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/ioctl.h>
#include <iostream>
#include <string>

using namespace std;

class SocketConnectException: public exception
{
  virtual const char* what() const throw()
  {
    return "Socket could not establish connection";
  }
} myex;

class Socket
{
    int32_t sock_fd;
    struct sockaddr_in servername;

    public:

        Socket(uint32_t port) 
        {
            // init socket file descriptor
            sock_fd = socket(PF_INET, SOCK_STREAM, 0);

            // file descriptor fail
            if (sock_fd < 0) {
                return;
            }

            /*
                AF_INET: Address Family
                htons:   Host to network short
            */
            servername.sin_family = AF_INET;
            servername.sin_port = htons(port);
        };

        bool Connect(const char *hostname) {
            std::cout << "Function connect(), hostname: " << hostname << std::endl;
            struct hostent *hostinfo = gethostbyname(hostname);
            
            // host not found
            if (hostinfo == NULL) {
                std::cout << "Hostinfo is NULL\n";
                return false;
            }

            servername.sin_addr = *(struct in_addr *) hostinfo->h_addr;

            if (0 > connect(sock_fd, (struct sockaddr *)&servername, sizeof(servername))) {
                std::cout << "Could not connect to socket" << std::endl;
                return false;
            }
            std::cout << "Connected to socket\n";
            return true;
        }

        bool Close() 
        { 
            close(sock_fd); 
            sock_fd = 0;
            return true; 
        }

        int32_t Write(std::string value)
        {
            // Write to socket file descriptor
            int32_t nbytes = ::write(sock_fd, value.c_str(), strlen(value.c_str()) + 1);
            std::cout << "nbytes written: " << nbytes << std::endl;
            if (nbytes < 0) {
                return 0;
            }
            
            return nbytes;
        }

        const std::string Read() 
        {            
            int32_t nbytes = 1024;

            //ioctl(sock_fd, FIONREAD, &nbytes);
            char *buffer = new char[nbytes];
            memset(buffer, 0x00, nbytes);
            if (nbytes > 0) {
                nbytes = ::read(sock_fd, buffer, nbytes);
                std::cout << "nbytes read " << nbytes << std::endl;
            }

            if (nbytes < 0) {
                printf("no bytes read\n");
            }
            else if (nbytes == 0) {
                printf("EOF\n");
            }
            
            std::string strBuffer(buffer);
            delete[] buffer;

            return strBuffer;
        }
};
