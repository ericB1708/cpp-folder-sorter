#pragma once

#include <map>
#include <list>
#include <string>
#include <vector>
#include <filesystem>

/**
 * @brief A utility class to automatically sort files into directories based on their file extensions.
 */
class FolderSort
{
private:
    std::map<std::string, std::list<std::string>> dictionaryFolderStructsAndTypes;
    std::string targetFolderPath;
    bool includeFoldersInSort;
    std::string includeFoldersInSortFolderName;

    /**
     * @brief Changes the current working directory to the target folder path.
     * @return true if the directory was successfully changed, false otherwise.
     */
    bool SwitchCheckDirectory();

    /**
     * @brief Handles and prints error messages to the standard error stream.
     * @param error The error message to display.
     */
    void onError(std::string error);

    /**
     * @brief Creates the necessary target directories based on the dictionary.
     */
    void CreateFolder();

    /**
     * @brief Moves a file or folder from a source path to a destination path.
     * @param source The current path of the file/folder.
     * @param destination The target path where the file/folder should be moved.
     * @return true if the move was successful, false otherwise.
     */
    bool MoveFileOrFolder(std::filesystem::path source, std::filesystem::path destination);

public:
    /**
     * @brief Initializes the FolderSort with a predefined dictionary.
     *
     * @param dictionaryFolderStructsAndTypes Map containing folder names as keys and a list of file extensions as values.
     * @param targetFolderPath The absolute path of the directory to be sorted.
     * @param includeFoldersInSort Determines whether to move unrecognized files/folders into a catch-all folder.
     */
    FolderSort(std::map<std::string, std::list<std::string>> dictionaryFolderStructsAndTypes, std::string targetFolderPath, bool includeFoldersInSort);

    /**
     * @brief Initializes the FolderSort without a predefined dictionary.
     *
     * @param targetFolderPath The absolute path of the directory to be sorted.
     * @param includeFoldersInSort Determines whether to move unrecognized files/folders into a catch-all folder.
     */
    FolderSort(std::string targetFolderPath, bool includeFoldersInSort);

    /**
     * @brief Default destructor.
     */
    ~FolderSort();

    /**
     * @brief Starts the sorting process in the target directory.
     *
     * Creates necessary folders and moves files based on the configured dictionary.
     */
    void SortFiles();

    /**
     * @brief Scans the target directory and prints all unique file extensions found.
     */
    void getAllExtensionOfFilesInFolder();

    /**
     * @brief Prints the current sorting dictionary to the standard output.
     */
    void printDictionary();

    /**
     * @brief Sets or overwrites the current sorting dictionary.
     * @param dictionaryFolderStructsAndTypes The new dictionary to be used for sorting.
     */
    void setDictionary(std::map<std::string, std::list<std::string>> dictionaryFolderStructsAndTypes);

    /**
     * @brief Sets a custom name for the catch-all folder and enables the catch-all feature.
     * @param includeFoldersInSortFolderName The name of the catch-all folder.
     */
    void setincludeFoldersInSortFolderName(std::string includeFoldersInSortFolderName);

    /**
     * @brief Converts a simple vector of extensions into a usable dictionary.
     *
     * Removes the dot ('.') from the extension to use it as the folder name.
     *
     * @param extensionOfFiles A vector of file extensions (e.g., {".png", ".jpg"}).
     * @return std::map<std::string, std::list<std::string>> The generated dictionary.
     */
    std::map<std::string, std::list<std::string>> listWithStringsToDictionary(std::vector<std::string> extensionOfFiles);
};
