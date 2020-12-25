//
// Created by nbdy on 20.12.20.
//

#ifndef PUI_BASEMODULE_H
#define PUI_BASEMODULE_H

#include <any>
#include <map>
#include <string>

#include <raylib.h>

#include <Shortcut/Shortcut.h>

typedef std::map<std::string, std::any> shareMap;
typedef std::map<std::string, shareMap> context;

enum ModuleTypes {
    UI = 0, BACKGROUND = 1
};

class Shortcut;

class BaseModule {
protected:
    bool visible = false;

    ModuleTypes type;
    bool sharing;

    std::string name;
    std::string description;
    std::string version;

    Shortcut *shortcut = nullptr;
    Widget *widget = nullptr;

public:
    BaseModule();

    /*!
     * call this in the managers work function
     * @return false if something is wrong and the module should be stopped
     */
    virtual bool work(const context& ctx);

    /*!
     * get a string representation of the module version
     * @return
     */
    virtual std::string getVersion();

    /*!
     * get the name of the module
     * @return
     */
    virtual std::string getName();

    /*!
     * get the description of the module
     * @return
     */
    virtual std::string getDescription();

    /*!
     * get the type of this module
     * @return
     */
    virtual uint8_t getType();

    /*!
     * does the module share its data
     * @return
     */
    virtual bool isSharing();

    /*!
     * get the modules shared data
     * @return
     */
    virtual shareMap getShareMap();

    /*!
     * is the module visible
     * @return
     */
    [[nodiscard]] bool isVisible() const;

    /*!
     * set if module is visible
     * @param value
     */
    void setVisible(bool value);

    /*!
     * can the module provide a shortcut
     * @return
     */
    bool hasShortcut();

    /*!
     * can the module provide a widget
     * @return
     */
    bool hasWidget();

    Widget* getWidget();

    Shortcut* getShortcut();
};

extern "C" BaseModule* create();

#endif //PUI_BASEMODULE_H
