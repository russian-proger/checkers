#pragma once

#include <algorithm>
#include <map>
#include <string>

struct Bridge {
    std::function<void(int,std::map<std::string,std::string>)> openForm;
    std::function<void()> exit;

    Bridge() {
        openForm = [](int,std::map<std::string,std::string> options={}){};
        exit = [](){};
    }
};