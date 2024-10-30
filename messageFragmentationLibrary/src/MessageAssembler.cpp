// src/MessageAssembler.cpp
#include "MessageAssembler.h"
#include <iostream>

MessageAssembler::MessageAssembler(int total_fragments, std::function<void(int)> missing_callback, int timeout_seconds)
    : total_fragments_(total_fragments), missing_callback_(missing_callback), timeout_seconds_(timeout_seconds) {
    start_time_ = std::chrono::steady_clock::now();
}

void MessageAssembler::add_fragment(const Fragment& fragment) {
    std::lock_guard<std::mutex> lock(mutex_);
    fragments_[fragment.sequence] = fragment.content;
}

bool MessageAssembler::assemble_message(std::string& message) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (is_complete()) {
        for (int i = 0; i < total_fragments_; ++i) {
            message += fragments_[i];
        }
        return true;
    } else if (has_timed_out()) {
        report_missing_fragments();
    }
    return false;
}

bool MessageAssembler::is_complete() {
    return fragments_.size() == total_fragments_;
}

void MessageAssembler::report_missing_fragments() {
    for (int i = 0; i < total_fragments_; ++i) {
        if (fragments_.find(i) == fragments_.end()) {
            missing_callback_(i);
        }
    }
}

bool MessageAssembler::has_timed_out() {
    auto current_time = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time_).count() > timeout_seconds_;
}

bool MessageAssembler::has_fragment(int sequence) const{
    return fragments_.find(sequence) != fragments_.end();
}

std::string MessageAssembler::get_fragment_content(int sequence) const{
    auto it = fragments_.find(sequence);
    return (it != fragments_.end()) ? it->second : "[MISSING]";
}