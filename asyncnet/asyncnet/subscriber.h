#include <zmq.hpp>
#include <iostream>

class subscriber
{
    
public:
    
    subscriber()
    {
        zmq::context_t context(1);
        zmq::socket_t subscriber(context, ZMQ_SUB);
        
        const char *loc = "tcp://localhost:5556";
        printf("connecting to %s\n", loc);
        subscriber.connect(loc);
        subscriber.setsockopt(ZMQ_SUBSCRIBE, "", 0);
    
    
        for (;;) {
            zmq::message_t message(5);
            subscriber.recv(&message, 0);
        
            printf("recv bytes %d message: \"%s\"\n", message.size(), message.data());
        }
    
        subscriber.close();
    }
    
};