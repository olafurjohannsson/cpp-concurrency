#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/ioctl.h>
#include <iostream>
#include <string>
#include <zmq.hpp>

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

        bool Close() 
        { 
            close(sock_fd); 
            sock_fd = 0;
            return true; 
        }

        ssize_t Write(std::string value)
        {
            // Write to socket file descriptor
            char buff[128];
            sprintf(buff, "test");
            ssize_t nbytes = ::write(sock_fd, buff, 128);  //value.c_str(), strlen(value.c_str()) + 1);
            
            return nbytes < 0 ? 0 : nbytes;
        }

        void Getaddrinfo(std::string address) {
            int status;
            struct addrinfo hints, *servinfo, *p;
            char ipstr[INET6_ADDRSTRLEN];

            memset(&hints, 0x00, sizeof(hints));
            hints.ai_family = AF_UNSPEC; // ipv4 or ipv6
            hints.ai_socktype = SOCK_STREAM; // tcp socket
            hints.ai_flags = AI_PASSIVE; // fill in my ip for me

            if ((status = getaddrinfo(address.c_str(), "80", &hints, &servinfo)) != 0) {
                printf("getaddrinfo err: %s\n", gai_strerror(status));
                exit(1); 
            }
            // servinfo now points to a linked list of 1 or more struct addrinfos
            for (p = servinfo; p != NULL; p = p->ai_next) {
                void *addr;
                char *ipver;

                if (p->ai_family == AF_INET) {
                    struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
                    addr = &(ipv4->sin_addr);
                    ipver = &std::string("IPv4")[0];
                }
                else {
                    // IPv6
                    
                }
                // convert IP to str
                inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));
                
                std::cout << "IP: " << ipver << "Str: " << ipstr << std::endl;
            }
            // ... do everything until you don't need servinfo anymore ....

            freeaddrinfo(servinfo); // free the linked-list
            std::cout << "returning from Getaddrinfo()\n";
            exit(0);
        }

        const std::string Read() 
        {
            size_t chunk_size = 256;
            ssize_t bytes_read;
            char buff[chunk_size];
            printf("starting to read\n");
            while ((bytes_read = ::read(this->sock_fd, &buff, chunk_size) > 0)) {
                printf("bytes_read: %d, buffer: %s\n", bytes_read, buff);
            }
            printf("done\n");
            return "";
            
            ssize_t nbytes = 1024;

            //ioctl(sock_fd, FIONREAD, &nbytes);
            char *buffer = new char[nbytes];
            memset(buffer, 0x00, nbytes);
            
            if (sock_fd > 0) {
                nbytes = ::read(sock_fd, buffer, nbytes);
                std::cout << "nbytes read " << nbytes << std::endl;
            }
            else {
                std::cout << "Socket descriptor is invalid\n";
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
