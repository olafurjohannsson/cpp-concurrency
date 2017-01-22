//
//  connector.h
//  asyncnet
//
//  Created by Ólafur Jóhannsson on 06/11/16.
//  Copyright © 2016 Ólafur Jóhannsson. All rights reserved.
//

#ifndef connector_h
#define connector_h

#include "socket.h"

// functor
template<Func>
bool doConnect(std::string port, Func fn)
{
    return fn(port);
}

// virtual function
class IConnector
{
    virtual bool connect(std::string port) = 0;
};

bool doConnect (std::string port, IConnector *connector)
{
    return connector->connect(port);
}


// tests
void test() {
    
    doConnect("123", nullptr);
}

#endif /* connector_h */
