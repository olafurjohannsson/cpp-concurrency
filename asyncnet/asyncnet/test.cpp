
/*
    C includes
*/
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

/*
    C++ STL includes
*/
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <string>
#include <functional>

/*
    Local header includes
*/
#include "socket.h"


std::string displayOptions() {
    return std::string(
        "1: Enter hostname\n" \
        "2: Write data\n" \
        "3: Read data\n" \
        "4: Get address information\n" \
        "\n"
    );
}


#include "subscriber.h"

int main()
{
    
    subscriber sub;
    
    return 0;
    /////////
    Socket s(80);
    if (s.Connect("visir.is")) {
        s.Write("test");
        std::cout << s.Read() << std::endl;
    }
    
    return 0;
    int32_t input, port;
    std::string hostname, address;
    bool connected = false;
    
    std::cout << "Creating socket, please input port: ";
    std::cin >> port;
    std::cout << "Setting up socket on port " << port << std::endl;
    Socket sock(port);

    for (;;) {
        std::cout << displayOptions();
        std::cin >> input;
        std::cin.clear();
        
        

        switch (input) {
            case 1:
                std::cout << "Enter hostname: ";
                std::cin >> hostname;
                
                if ((connected = sock.Connect(hostname.c_str()))) {
                    std::cout << "Successfully connected to " << hostname << std::endl;
                }
                else { 
                    std::cout << "Could not establish connection\n";
                }
                break;
                
            case 2:
                std::cout << "Data: ";
                if (sock.Write(std::string(std::istreambuf_iterator<char>(std::cin), {})) > 0)
                {
                    std::cout << "Response: " << sock.Read() << std::endl;
                }
                
                break;
                
            case 4:
                std::cout << "Enter address name:";
                
                std::cin >> address;
                sock.Getaddrinfo(address);



                break;

            default:
                continue;
        };
    }

    return 0;
}
