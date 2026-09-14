#include "FolderSort.h"
#include <iostream>
#include <locale>
#include <codecvt>
#include <filesystem>
#include <string>
#include <vector>
#include <algorithm>
#include <string>
#include <cctype>

// ----------------------------------------------------------------------------
// Constructors & Destructor
// ----------------------------------------------------------------------------
FolderSort::FolderSort(std::map<std::string, std::list<std::string>> dictionaryFolderStructsAndTypes, std::string targetFolderPath, bool includeFoldersInSort)
{
    this->dictionaryFolderStructsAndTypes = dictionaryFolderStructsAndTypes;
    this->targetFolderPath = targetFolderPath;
    this->includeFoldersInSort = includeFoldersInSort;
    this->includeFoldersInSortFolderName = "Folder"; // Default name for the catch-all folder
}

FolderSort::FolderSort(std::string targetFolderPath, bool includeFoldersInSort)
{
    this->targetFolderPath = targetFolderPath;
    this->includeFoldersInSort = includeFoldersInSort;
    this->includeFoldersInSortFolderName = "Folder";
}

FolderSort::~FolderSort()
{
}

// ----------------------------------------------------------------------------
// Public API Methods
// ----------------------------------------------------------------------------

void FolderSort::SortFiles()
{
    bool moved = false;

    // Step 1: Ensure we are in the correct target directory before doing anything
    if (this->SwitchCheckDirectory())
    {
        // Step 2: Create all necessary target directories based on the dictionary
        this->CreateFolder();
        std::string path = ".";
        // Step 3: Iterate through all items in the current directory
        for (const auto &entry : std::filesystem::directory_iterator(path))
        {
            if (entry.is_regular_file())
            {
                // Extract the file extension and convert it to lowercase (e.g., .JPG -> .jpg)
                std::string fileExtension = entry.path().extension().string();
                std::transform(fileExtension.begin(), fileExtension.end(), fileExtension.begin(), [](unsigned char c)
                               { return std::tolower(c); });

                // Check the file extension against our dictionary
                for (const auto &[key, value] : this->dictionaryFolderStructsAndTypes)
                {
                    for (const auto &i : value)
                    {
                        if (fileExtension == i)
                        {
                            // Construct paths and move the file
                            std::filesystem::path source = entry.path();
                            std::filesystem::path destination = std::filesystem::current_path() / key / entry.path().filename();
                            this->MoveFileOrFolder(source, destination);
                            moved = true;
                            break; // Break inner loop since the file is moved
                        }
                    }
                    if (moved == true)
                        break; // Break outer loop to process the next file
                }
                moved = false; // Reset for the next iteration
            }
            // Step 4: Handle folders or unrecognized files if the catch-all option is enabled
            else if (this->includeFoldersInSort)
            {
                bool isASortFolder = false;

                // Verify that the current item is not one of our designated sorting folders
                for (const auto &[key, value] : this->dictionaryFolderStructsAndTypes)
                {
                    if (key == entry.path().filename()) // Added .string() for safe comparison
                    {
                        isASortFolder = true;
                        break;
                    }
                }
                // If it's not a sorting folder AND not the catch-all folder itself, move it
                if (!isASortFolder && entry.path().filename() != this->includeFoldersInSortFolderName)
                {

                    std::filesystem::path source = entry.path();
                    std::filesystem::path destination = std::filesystem::current_path() / this->includeFoldersInSortFolderName / entry.path().filename();
                    this->MoveFileOrFolder(source, destination);
                }
            }
        }
    }
}

void FolderSort::getAllExtensionOfFilesInFolder()
{
    std::vector<std::string> extensionOfFiles;
    if (this->SwitchCheckDirectory())
    {
        std::string path = ".";
        for (const auto &entry : std::filesystem::directory_iterator(path))
        {
            // Check if the extension is already in our list to avoid duplicates
            if (std::find(extensionOfFiles.begin(), extensionOfFiles.end(), entry.path().extension().string()) != extensionOfFiles.end())
            {
                // Extension already exists; do nothing
            }
            else
            {
                // New extension found; add it to the list
                extensionOfFiles.push_back(entry.path().extension().string());
            }
        }

        // Print all unique extensions formatted as a comma-separated list of strings
        for (auto &&i : extensionOfFiles)
        {
            std::cout << "\"" << i << "\"" << ",";
        }
    }
}

std::map<std::string, std::list<std::string>> FolderSort::listWithStringsToDictionary(std::vector<std::string> extensionOfFiles)
{
    std::map<std::string, std::list<std::string>> dictionaryFolderStructsAndTypes;

    for (std::string i : extensionOfFiles)
    {
        std::string originalExtension = i;

        // Erase-Remove Idiom: Removes all dots ('.') from the extension to use it as a folder name
        i.erase(std::remove(i.begin(), i.end(), '.'), i.end());
        dictionaryFolderStructsAndTypes[i].push_back(originalExtension);
    }
    return dictionaryFolderStructsAndTypes;
}

void FolderSort::printDictionary()
{
    // Iterate through the map and print keys and their associated lists
    for (const auto &[key, value] : this->dictionaryFolderStructsAndTypes)
    {
        std::cout << key << ": ";
        for (auto &&i : value)
        {
            std::cout << i << ",";
        }
        std::cout << std::endl;
    }
}

void FolderSort::setDictionary(std::map<std::string, std::list<std::string>> dictionaryFolderStructsAndTypes)
{
    this->dictionaryFolderStructsAndTypes = dictionaryFolderStructsAndTypes;
}

void FolderSort::setincludeFoldersInSortFolderName(std::string includeFoldersInSortFolderName)
{
    this->includeFoldersInSortFolderName = includeFoldersInSortFolderName;
    this->includeFoldersInSort = true;
}

// ----------------------------------------------------------------------------
// Private Helper Functions
// ----------------------------------------------------------------------------
bool FolderSort::SwitchCheckDirectory()
{

    bool successOfSetDict = false;
    // Only attempt to change the directory if we aren't already there
    if (std::filesystem::current_path() != this->targetFolderPath)
    {

        try
        {
            std::filesystem::current_path(this->targetFolderPath);

            // Double-check if the directory change was successful
            if (std::filesystem::current_path() == this->targetFolderPath)
            {
                std::cout << "Successfully changed to: " << this->targetFolderPath << std::endl;
                successOfSetDict = true;
            }
        }
        catch (const std::filesystem::filesystem_error &e)
        {
            // Catch permissions or non-existent folder errors
            this->onError(e.what());
        }
    }
    else
    {
        // We are already in the correct directory
        successOfSetDict = true;
    }

    return successOfSetDict;
}

void FolderSort::onError(std::string error)
{
    std::cerr << "Failed to change directory. Error: " << error << std::endl;
}

void FolderSort::CreateFolder()
{
    if (this->SwitchCheckDirectory())
    {
        // Create all directories defined in the dictionary keys
        for (const auto &[key, value] : this->dictionaryFolderStructsAndTypes)
        {
            if (std::filesystem::create_directory(key))
            {
                std::cout << "Directory created successfully.\n";
            }
            else
            {
                // std::cout << "Failed to create directory or it already exists: " << key << "\n";
            }
        }

        // Create the catch-all folder if the feature is enabled
        if (this->includeFoldersInSort)
        {
            if (std::filesystem::create_directory(this->includeFoldersInSortFolderName))
            {
                std::cout << "Directory created successfully.\n";
            }
            else
            {
                // std::cout << "Failed to create directory or it already exists.\n";
            }
        }
    }
}

bool FolderSort::MoveFileOrFolder(std::filesystem::path source, std::filesystem::path destination)
{
    bool success = false;
    std::error_code ec;

    // Perform the filesystem move operation
    std::filesystem::rename(source, destination, ec);

    if (ec)
    {
        std::cerr << "Error: " << ec.message() << '\n';
        std::cout << "Source : " << source << std::endl;
        std::cout << "Destination : " << destination << std::endl;
    }
    else
    {
        std::cout << "File moved successfully.\n";
        success = true;
    }
    return success;
}
