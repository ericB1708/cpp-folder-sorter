cmake_minimum_required(VERSION 3.10)
project(FolderSorter)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


add_subdirectory(folder_sort_lib)
add_subdirectory(app)