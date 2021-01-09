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

    Texture2D texLoadedModules;
    Texture2D texLoadableModules;
    Texture2D texDownloadableModules;
    Texture2D texUpdateableModules;
    Texture2D texSettings;

    Texture2D texControlButtons[5] = {texLoadedModules, texLoadableModules, texDownloadableModules, texUpdateableModules, texSettings};

    void drawControlButtons() {
        for(auto t : texControlButtons) {
            // todo
        }
    }

    void showLoadedModules(void *data) { // todo
        auto *mm = ((Manager*) data)->getModuleManager();
        for(auto m : mm->getLoadedModules()) {

        }
    };

    void showLoadableModules(void *data) {}; // todo
    void showDownloadableModules(void *data) {}; // todo
    void showSettings(void *data) {}; // todo

    void loadTextures() {
        texLoadedModules = Utils::getIcon("modules", Vector2 {});
    }

    void unloadTextures() {
        // todo
    }

public:
    ModuleStore(): BaseModule("ModuleStore", "(Down/Un)Load Modules", "0.1", "modules", UI, false) {
        loadTextures();
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