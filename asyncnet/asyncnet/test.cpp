
/*
    C includes
*/
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

/*
    C++ includes
    Mostly STL
*/
#include <iostream>
#include <thread>
#include <chrono>
#include <string>

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

bool isdigit1(std::string s) {
    return false;
}

bool filterDigit2(std::string value) {
    std::string::const_iterator it;
    for (it = value.begin(); it != value.end() && std::isdigit(*it); ++it)
        ;
    return !value.empty() && it == value.end();
}

int main()
{   
    int32_t input, port;
    std::string hostname, address;
    bool connected = false;
    
    std::cout << "Creating socket, please input port: ";
    std::cin >> port;
    std::cout << "Setting up socket on port " << port << std::endl;
    Socket sock(port);

    //std::string s;
    
    bool filterDigit = [](std::string value) {
        return !value.empty() && std::find_if(value.begin(), value.end(), [](char c) {
            return !std::isdigit(c);
        }) == value.end();
    };

    


    for (;;) {
        std::cout << displayOptions();
        std::cin >> input;
        
        

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
/*
    Socket sock(80);
    std::cout << "works" << std::endl;

    if (sock.Connect("google.com")) {
        std::cout << "connected\n";

        // for 2s
        // does not work on osx 
        // using namespace std::chrono_literals;
        for (;;) {

            int written = sock.Write("test");

            std::this_thread::sleep_for(
                    std::chrono::seconds(2));

            std::cout << "starting read\n";
            std::string r = sock.Read();
            std::cout << "read done\n";
            if (!r.empty()) {
                printf("r: %s\n", r.c_str());
            }
        }

        sock.Close();

    }
    return 0;
    */
}
