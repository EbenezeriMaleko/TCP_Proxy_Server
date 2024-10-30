#include "MessageFragmenter.h"
#include "MessageAssembler.h"
#include <iostream>
#include <thread> // Include for std::this_thread
#include <vector> // Include for std::vector

int main() {
    std::string message;
    std::cout << "Enter a message to be fragmented: ";
    std::getline(std::cin, message);

    int fragment_size;
    std::cout << "Enter Chunk size: ";
    std::cin >> fragment_size;

    // Fragment the message using user-defined fragment size
    auto fragments = MessageFragmenter::fragment_message(message, fragment_size);

    // Define missing fragment callback
    auto missing_callback = [](int missing_seq) {
        std::cerr << "Chunk " << missing_seq << " is missing.\n";
    };

    // Initialize assembler with a 5-second timeout
    MessageAssembler assembler(fragments.size(), missing_callback, 5);

    // Simulate reassembling fragments (drop one fragment to simulate a missing piece)
    for (size_t i = 0; i < fragments.size(); ++i) {
        if (i != 2) { // Let's assume fragment 2 is missing
            assembler.add_fragment(fragments[i]);
        }
    }

    // Wait to simulate timeout for reassembly
    std::this_thread::sleep_for(std::chrono::seconds(6));

    // Attempt to assemble message
    std::string assembled_message;
    if (assembler.assemble_message(assembled_message)) {
        std::cout << "Message assembled successfully: " << assembled_message << std::endl;
    } else {
        std::cout << "Message assembly incomplete due to missing or corrupted data.\n";
        std::cout << "Partially assembled message: ";

        assembled_message.clear();

        for (int i = 0; i < fragments.size(); i++) {
            if (assembler.has_fragment(i)) {
                assembled_message += assembler.get_fragment_content(i);
            } else {
                assembled_message += "[MISSING]";
            }
        }
        std::cout << assembled_message << std::endl;
    }

    return 0;
}
