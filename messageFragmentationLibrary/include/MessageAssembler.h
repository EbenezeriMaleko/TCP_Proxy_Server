 // include/MessageAssembler.h
#pragma once
#include "Fragment.h"
#include <unordered_map>
#include <string>
#include <functional>
#include <chrono>
#include <mutex>

class MessageAssembler {
public:
    MessageAssembler(int total_fragments, std::function<void(int)> missing_callback, int timeout_seconds);
    
    // Add a fragment to the assembler
    void add_fragment(const Fragment& fragment);

    // Attempt to assemble the message
    bool assemble_message(std::string& message);
    bool has_fragment(int sequence) const;
    std::string get_fragment_content(int sequence) const;

private:
    std::unordered_map<int, std::string> fragments_;
    int total_fragments_;
    int timeout_seconds_;
    std::function<void(int)> missing_callback_;
    std::chrono::steady_clock::time_point start_time_;
    std::mutex mutex_;

    // Check if all fragments are received
    bool is_complete();

    // Report any missing fragments
    void report_missing_fragments();

    // Check if reassembly has timed out
    bool has_timed_out();
};
