# C++ Message Fragmentation Library

This project is a C++ library for fragmenting and reassembling messages, with features for handling missing and corrupted fragments.

## Features
- **Message Fragmentation**: Split messages into small, numbered fragments.
- **Message Reassembly**: Rebuilds messages from received fragments, with checks for missing or corrupted chunks.
- **Error Reporting**: Detects missing chunks and triggers callbacks.

## Folder Structure
- `include/`: Header files for the library classes.
- `src/`: Source files implementing the classes.

## Build Instructions
```bash
mkdir build
cd build
cmake ..
make
