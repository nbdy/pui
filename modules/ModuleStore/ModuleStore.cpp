//
// Created by nbdy on 04.01.21.
//

#include <BaseModule/BaseModule.h>
#include <Manager/Manager.h>

#define CTRL_BUTTON_SIZE Vector2 {16, 16}

enum ModuleStoreUIState {
    LOADED = 0, LOADABLE, DOWNLOADABLE, SETTINGS
};

class ModuleStore : public BaseModule {
protected:
    ModuleStoreUIState state = LOADED;

    void drawControlButtons() {
    }

    void showLoadedModules(void *data) { // todo
        auto *mm = ((Manager*) data)->getModuleManager();
        for(auto m : mm->getLoadedModules()) {

        }
    };

    void showLoadableModules(void *data) {}; // todo
    void showDownloadableModules(void *data) {}; // todo
    void showSettings(void *data) {}; // todo

    void unloadTextures() {
        // todo
    }

public:
    ModuleStore(): BaseModule() {

    }

    ~ModuleStore() {
        // unloadTextures();
    }

    void loop(void *data) override {
        switch (state) {
            case LOADED: showLoadedModules(data); break;
            case LOADABLE: showLoadableModules(data); break;
            case DOWNLOADABLE: showDownloadableModules(data); break;
            case SETTINGS: showSettings(data); break;
        }
    }

    bool work(void *data, const context &ctx) override {
        return true;
    }
};

extern "C" tModule* create() {
    return dynamic_cast<ModuleStore*>(new ModuleStore);
};