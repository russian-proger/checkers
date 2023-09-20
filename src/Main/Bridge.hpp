#pragma once

#include <algorithm>

struct Bridge {
    std::function<void(int)> openForm;
    std::function<void()> exit;
    Bridge() {
        openForm = [](int){};
        exit = [](){};
    }
};