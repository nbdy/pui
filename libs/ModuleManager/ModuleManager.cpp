//
// Created by nbdy on 20.12.20.
//

#include "ModuleManager.h"

std::vector<std::string> ModuleManager::listModules(std::string path) {
    if(!fplus::is_suffix_of(std::string("/"), path)) path += "/";
    return fplus::keep_if([](const std::string& v) {return fplus::is_suffix_of(v, std::string(".so"));}, Utils::listDirectory(path));
}

BaseModule *ModuleManager::createModule(const std::string &path) {
    void* h = dlopen(path.c_str(), RTLD_LAZY);
    BaseModule* (*create)();
    create = (BaseModule* (*)()) dlsym(h, "create");
    return (BaseModule*) create();
}

ModuleManager::ModuleManager(const std::string &path) {

}

ModuleManager::~ModuleManager() = default;

ModuleManager::ModuleManager() = default;
