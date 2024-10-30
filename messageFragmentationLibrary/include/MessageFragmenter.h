#pragma once
#include "Fragment.h"
#include <vector>
#include <string>

class MessageFragmenter {
public:
    static std::vector<Fragment> fragment_message(const std::string& message, size_t fragment_size);
};
