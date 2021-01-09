//
// Created by nbdy on 20.12.20.
//

#ifndef PUI_BASEMODULE_H
#define PUI_BASEMODULE_H

#include <any>
#include <map>
#include <string>

#include <raylib.h>
#include <Utils/Utils.h>

#define SHORTCUT_SIZE Vector2 {96, 96}

typedef std::map<std::string, std::any> shareMap;
typedef std::map<std::string, shareMap> context;

enum ModuleTypes {
    UI = 0, BACKGROUND = 1
};

class BaseWidget;

class BaseModule {
protected:
    bool error = false;
    std::string errorMessage;

    ModuleTypes type;
    bool sharing;

    std::string name;
    std::string description;
    std::string version;

    Texture2D shortcut {};
    BaseWidget* widget;

public:
    BaseModule();
    BaseModule(std::string name, std::string description, std::string version);
    BaseModule(std::string name, std::string description, std::string version, const std::string& shortcutName);
    BaseModule(std::string name, std::string description, std::string version,
               const std::string& shortcutName, ModuleTypes type, bool sharing);

    virtual ~BaseModule();

     /*!
     * call this in the managers work function
     * @return false if something is wrong and the module should be stopped
     */
    virtual bool work(void* data, const context& ctx);

    virtual void drawWidget(void* data);

    virtual void loop(void* data);

    /*!
     * get a string representation of the module version
     * @return
     */
    std::string getVersion();

    /*!
     * get the name of the module
     * @return
     */
    std::string getName();

    /*!
     * get the description of the module
     * @return
     */
    std::string getDescription();

    /*!
     * get the type of this module
     * @return
     */
    uint8_t getType();

    /*!
     * does the module share its data
     * @return
     */
    [[nodiscard]] bool isSharing() const;

    /*!
     * get the modules shared data
     * @return
     */
    virtual shareMap getShareMap();

    bool shortcutClicked(Rectangle bounds, const char* text);

    virtual void backButtonClicked(void *data);

    void setError(const std::string& msg);
    [[nodiscard]] bool hasError() const;
    std::string getErrorMessage();

    void deallocate();
};

typedef BaseModule tModule;
typedef tModule* ptModule;
typedef ptModule create_t();
typedef std::vector<ptModule> modVec;
typedef std::map<std::string, ptModule> strModMap;

class BaseWidget {
protected:
    time_t* clicked = nullptr;
    Rectangle bounds{};
    ptModule module{};

public:
    BaseWidget();
    BaseWidget(Rectangle bounds, ptModule module);
    virtual ~BaseWidget();

    virtual bool onClicked();
    virtual bool onLongClicked();

    void loop(void* data);
    void work(context ctx, void* data);
};

// typedef void destroy_(BaseModule*);

#endif //PUI_BASEMODULE_H
