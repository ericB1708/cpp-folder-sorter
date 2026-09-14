# C++ Folder Sorter 📂

A robust, modern C++ library and command-line application that automatically organizes files in a directory based on their file extensions. 

This project was built to demonstrate proficiency in modern C++ features (C++17), STL containers, and professional CMake project structuring.

## ✨ Features
* **Automated Sorting:** Maps specific file extensions to target directories (e.g., `.jpg`, `.png` -> `Bilder`).
* **Catch-All Directory:** Optionally moves all unknown or unmapped files into a designated fallback folder.
* **Modern C++17:** Heavily utilizes `std::filesystem` for robust and cross-platform path manipulation and file moving.
* **STL Containers:** Uses `std::map`, `std::list`, and `std::vector` for efficient data handling and lookup.
* **Modular Architecture:** Structured into a shared dynamic library (`.dll`) and an executable application (`.exe`) using CMake.

## 🏗️ Project Structure
```text
├── app/                  # The executable application
│   ├── src/main.cpp
│   └── CMakeLists.txt
├── folder_sort_lib/      # The shared C++ library
│   ├── include/          # Public headers (Doxygen documented)
│   ├── src/              # Implementation files
│   └── CMakeLists.txt
├── CMakeLists.txt        # Top-level CMake configuration
└── README.md

```

## 🚀 How to Build

This project uses CMake as its build system.

1. Clone the repository:
```bash
git clone 
cd folder-sorter

```


2. Configure the project:
```bash
cmake -S . -B build

```


3. Build the project:
```bash
cmake --build build

```



## 💻 Usage Example

```cpp
#include "FolderSort.h"

int main() {
    // Define mapping: Folder Name -> List of Extensions
    std::map<std::string, std::list<std::string>> dictionary = {
        {"Images", {".jpg", ".png", ".avif"}},
        {"Documents", {".pdf", ".docx"}}
    };

    // Initialize with target directory and enable the catch-all folder
    FolderSort sorter(dictionary, "C:/Users/Name/Downloads", true);
    
    // Execute the sorting process
    sorter.SortFiles();

    return 0;
}

```


