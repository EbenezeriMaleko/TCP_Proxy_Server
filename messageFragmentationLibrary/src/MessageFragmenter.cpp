// src/MessageFragmenter.cpp
#include "MessageFragmenter.h"

std::vector<Fragment> MessageFragmenter::fragment_message(const std::string& message, size_t fragment_size) {
    std::vector<Fragment> fragments;
    int sequence = 0;

    for (size_t i = 0; i < message.size(); i += fragment_size) {
        Fragment fragment{sequence++, message.substr(i, fragment_size)};
        fragments.push_back(fragment);
    }

    return fragments;
}
