//
// Created by nbdy on 20.12.20.
//

#ifndef PUI_MODULEMANAGER_H
#define PUI_MODULEMANAGER_H

#include <map>
#include <dlfcn.h>

#include <fplus.h>

#include <Utils/Utils.h>
#include <BaseModule/BaseModule.h>

class ModuleManager {
    std::vector<std::string> loadableModules;
    std::map<std::string, BaseModule*> loadedModules;

public:
    ModuleManager();
    explicit ModuleManager(const std::string& path);

    ~ModuleManager();

    /*!
     * puts all .so files in a vector
     * prefixes the file with the supplied path
     * @param path
     * @return
     */
    static std::vector<std::string> listModules(std::string path);

    /*!
     * creates an instance of the specified shared object
     * the developer is in charge of deleting the instance
     * @param path
     * @return
     */
    static BaseModule* createModule(const std::string& path);
};


#endif //PUI_MODULEMANAGER_H
