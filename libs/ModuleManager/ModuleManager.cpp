//
// Created by nbdy on 20.12.20.
//

#include "ModuleManager.h"

ModuleManager::ModuleManager() {}

ModuleManager::ModuleManager(const std::string &path) {
    moduleDirectory = path;
    loadableModules = listModules(path);
}

std::vector<std::string> ModuleManager::listModules(std::string path) {
    if(!fplus::is_suffix_of(std::string("/"), path)) path += "/";
    return fplus::keep_if([](const std::string& v) {return fplus::is_suffix_of(std::string(".so"), v);}, Utils::listDirectory(path));
}

BaseModule *ModuleManager::createModule(const std::string &path) {
    void* h = dlopen(path.c_str(), RTLD_LAZY);
    if(!h) {
        LOG_F(WARNING, "Could not load module '%s'.", path.c_str());
        LOG_F(WARNING, "Due to: %s", dlerror());
        return nullptr;
    }
    auto* create = (create_t*) dlsym(h, "create");
    auto error = dlerror();
    if(error) {
        LOG_F(WARNING, "Could not load symbol '%s'.", "create");
        LOG_F(WARNING, "Due to: %s", error);
        return nullptr;
    }
    auto* t = create();
    dlclose(h);
    return t;
}

void ModuleManager::loadAllModules() {
    loadModules(loadableModules);
}

void ModuleManager::loadModules(const strVec& modules) {
    for(const auto& m : modules) {
        if(fplus::map_contains(loadedModules, m)) continue; // skip if we already loaded the module
        if(fplus::is_elem_of(m, loadableModules)) {
            auto *lm = createModule(m);
            if(lm != nullptr) loadedModules[m] = lm;
        }
    }
}

context ModuleManager::accumulateContext() {
    context r;
    for(auto& lm : loadedModules) {
        if(lm.second->isSharing()) r[lm.second->getName()] = lm.second->getShareMap();
    }
    return r;
}

void ModuleManager::unloadModules(const strVec &modules) {
    for(const auto& m : modules) {
        if(!fplus::map_contains(loadedModules, m)) continue; // skip if module is not loaded
        if(fplus::is_elem_of(m, fplus::get_map_keys(loadedModules))) {
            delete loadedModules[m];
            loadedModules.erase(m);
        }
    }
}

void ModuleManager::unloadAllModules() {
    unloadModules(fplus::get_map_keys(loadedModules));
    loadedModules.clear();
}

void ModuleManager::work(void* data, const context& ctx) {
    for(auto& lm : loadedModules) lm.second->work(data, ctx);
}

std::string ModuleManager::getModuleDirectory() const {
    return moduleDirectory;
}

void ModuleManager::setModuleDirectory(const std::string &value) {
    moduleDirectory = value;
    unloadAllModules();
    loadableModules.clear();
    loadableModules = listModules(value);
}

strVec ModuleManager::getLoadableModules() {
    return loadableModules;
}

std::vector<BaseModule*> ModuleManager::getLoadedModules() {
    return fplus::get_map_values(loadedModules);
}

ModuleManager::~ModuleManager() = default;
