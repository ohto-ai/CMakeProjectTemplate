#include <iostream>
#include <version.h>

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::cout << "AppName: " << VersionHelper::getInstance().AppName << std::endl;
    std::cout << "Author: " << VersionHelper::getInstance().Author << std::endl;
    std::cout << "Email: " << VersionHelper::getInstance().Email << std::endl;
    std::cout << "Version: " << VersionHelper::getInstance().Version << std::endl;
    std::cout << "GitDescribe: " << VersionHelper::getInstance().GitDescribe << std::endl;
    std::cout << "GitSha1: " << VersionHelper::getInstance().GitSha1 << std::endl;
    std::cout << "GitRefSpec: " << VersionHelper::getInstance().GitRefSpec << std::endl;
    std::cout << "BuildDate: " << VersionHelper::getInstance().BuildDate << std::endl;
    std::cout << "BuildTime: " << VersionHelper::getInstance().BuildTime << std::endl;
    return 0;
}
