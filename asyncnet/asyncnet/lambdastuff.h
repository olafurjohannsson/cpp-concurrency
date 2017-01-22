//
//  lambdastuff.h
//  asyncnet
//
//  Created by Ólafur Jóhannsson on 06/11/16.
//  Copyright © 2016 Ólafur Jóhannsson. All rights reserved.
//

#ifndef lambdastuff_h
#define lambdastuff_h


auto filterDigit = [] (std::string value) -> bool {
    return !value.empty() && std::find_if(value.begin(), value.end(), [](char c) {
        return !std::isdigit(c);
    }) == value.end();
};

bool isdigit1(std::string s) {
    return false;
}

bool filterDigit2(std::string value) {
    std::string::const_iterator it;
    for (it = value.begin(); it != value.end() && std::isdigit(*it); ++it)
        ;
    return !value.empty() && it == value.end();
}

vector<int> vec;

template<typename Func>
std::vector<int> find(Func func)
{
    std::vector<int> result;
    for_each(vec.begin(), vec.end(), [&] (int v) {
        if (func(v)) {
            result.push_back(v);
        }
    });
    return result;
}

int find2(std::function<bool (int)> func) {
    for_each(vec.begin(), vec.end(), [=] (int v) {
        
    });
    return 0;
}

int test() {
    
    // lambda to automatic var
    auto print = [] (int value) -> void { std::cout << std::to_string(value) << std::endl; };
    
    // lambda to function pointer
    typedef int (*fn)();
    fn f = [] () -> int32_t { return 1337; };
    
    // lambda to std::function
    std::function<int ()> function = [] () -> int32_t {
        return 1000;
    };
    
    
    vec.push_back(function());
    vec.push_back(f());
    
    for_each(vec.begin(), vec.end(), [&] (int v) {
        print(v);
    });
    auto fff = find([] (int v) {
        return v == 1000;
    });
    
    
    
    return 0;
}

#endif /* lambdastuff_h */
