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

typedef std::vector<std::string> strVec;
typedef std::map<std::string, BaseModule*> moduleMap;

class ModuleManager {
    std::string moduleDirectory;
    strVec loadableModules;
    moduleMap loadedModules;

public:
    ModuleManager();

    /*!
     * initializes the module manager with the given path
     * @param path
     */
    explicit ModuleManager(const std::string& path);

    ~ModuleManager();

    /*!
     * get all loadable module names
     * @return
     */
    strVec getLoadableModules();

    /*!
     * returns all currently loaded modules
     * @return
     */
     std::vector<BaseModule*> getLoadedModules();

    /*!
     * loads all available modules
     */
    void loadAllModules();

    /*!
     * loads only the specified modules
     * @param modules
     */
    void loadModules(const strVec& modules);

    /*!
     * unloads all modules
     */
    void unloadAllModules();

    /*!
     * unloads only the specified modules
     * @param modules
     */
    void unloadModules(const strVec& modules);

    /*!
     * collects all shareMaps from modules
     * @return
     */
    context accumulateContext();

    /*!
     * calls work() on all modules
     * @param ctx
     */
    void work(void* data, const context& ctx);

    /*!
     * calls draw() on all modules
     */
    void drawModules();

    /*!
     * get the module directory
     * @return
     */
    [[nodiscard]] std::string getModuleDirectory() const;

    /*!
     * sets the module directory
     * unloads all modules
     * does not load modules in this directory
     * loadAllModules has to be called by the developer
     * @param value
     */
    void setModuleDirectory(const std::string& value);

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
