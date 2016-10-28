#include <iostream>
#include <thread>
#include <chrono>
#include "socket.h"

int main()
{
    Socket sock(80);
    std::cout << "works" << std::endl;
    
    if (sock.Connect("127.0.0.1")) {
        std::cout << "connected\n";

        // for 2s
        using namespace std::chrono_literals;
        for (;;) {

            int written = sock.write_to_server("test");

            std::cout << "written: " << written << std::endl;

            std::this_thread::sleep_for(2s);

            sock.read();
        }

    }
    return 0;

}
