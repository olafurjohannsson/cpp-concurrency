#include <iostream>
#include <thread>
#include <chrono>
#include "socket.h"

int main()
{
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

}
