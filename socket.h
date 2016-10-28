#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

class Socket
{
    
    public:
        Socket() 
        {
            int32_t sock;
            uint32_t port;
            struct sockaddr_in servername;

            sock = socket(PF_INET, SOCK_STREAM, 0);

            port = 80;

            if (sock < 0)
            {
                perror("socket error");
                exit(EXIT_FAILURE);
            }

            init_sockaddr(&servername, "127.0.0.1", port);

            if (0 > connect(sock, (struct sockaddr *)&servername, sizeof(servername)))
            {
                perror("connect error");
                exit(EXIT_FAILURE);
            }
            
            char msg_buffer[4];
            strncpy(msg_buffer, "asdf", 4);
            write_to_server(sock, msg_buffer);

            close(sock);
        };

    private:

        void write_to_server(int fd, char *message)
        {
            int nbytes = write(fd, message, strlen(message) + 1);
            if (nbytes < 0)
            {
                perror("write");
                exit(EXIT_FAILURE);
            }
        }

        void init_sockaddr(struct sockaddr_in *name, const char *hostname, uint16_t port)
        {
            struct hostent *hostinfo;

            name->sin_family = AF_INET;
            name->sin_port = htons(port);
            hostinfo = gethostbyname(hostname);

            if (hostinfo == NULL)
            {
                printf("Unknown host %s.\n", hostname);
                exit(EXIT_FAILURE);
            }
            name->sin_addr = *(struct in_addr *) hostinfo->h_addr;
        }
};
