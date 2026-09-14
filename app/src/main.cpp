#include "FolderSort.h"
#include <iostream>

int main(int argc, char const *argv[])
{
    // std::vector<std::string> extensionOfFiles = {".pdf", ".mp3", ".mp4", ".jpg", ".msix", ".exe", "", ".png", ".msi", ".docx", ".jar", ".zip", ".avif", ".mrpack", ".json", ".1_Windows", ".svg", ".ini", ".webp", ".pptx", ".JPG", ".hideout", ".drp", ".1-windows-amd64", ".iso", ".csv"};
    std::map<std::string, std::list<std::string>> dictionaryFolderStructsAndTypes;
    dictionaryFolderStructsAndTypes["PDF"] = {".pdf"};
    dictionaryFolderStructsAndTypes["Audio"] = {".mp3"};
    dictionaryFolderStructsAndTypes["Videos"] = {".mp4"};
    dictionaryFolderStructsAndTypes["Bilder"] = {".jpg", ".png", ".svg", ".webp", ".avif"};
    dictionaryFolderStructsAndTypes["Anwendungen"] = {".exe", ".1_Windows", ".1-windows-amd64"};
    dictionaryFolderStructsAndTypes["Installer"] = {".msi", ".msix"};
    dictionaryFolderStructsAndTypes["Word"] = {".docx"};
    dictionaryFolderStructsAndTypes["PowerPoint"] = {".pptx"};
    dictionaryFolderStructsAndTypes["ZIP"] = {".zip"};
    dictionaryFolderStructsAndTypes["Modrinth_MC_modpacks"] = {".mrpack"};
    dictionaryFolderStructsAndTypes["JSON"] = {".json"};
    dictionaryFolderStructsAndTypes["CSV"] = {".csv"};
    dictionaryFolderStructsAndTypes["ISO"] = {".iso"};
    dictionaryFolderStructsAndTypes["Java"] = {".jar"};
    dictionaryFolderStructsAndTypes["Config"] = {".ini"};
    dictionaryFolderStructsAndTypes["DaVinci Resolve"] = {".drp"};
    dictionaryFolderStructsAndTypes["Path of Exile Hideouts"] = {".hideout"};
    dictionaryFolderStructsAndTypes["Ohne_Endung"] = {""};
    FolderSort test("C:/Users/ericb/Downloads", true);
    test.setDictionary(dictionaryFolderStructsAndTypes);
    // test.getAllExtensionOfFilesInFolder();
    test.setincludeFoldersInSortFolderName("Ordner");
    test.SortFiles();
    // auto ret = test.listWithStringsToDictionary(extensionOfFiles);
    // test.setDictionary(ret);
    // test.printDictionary();

    //  test.SortFiles();

    return 0;
}
