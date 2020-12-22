//
// Created by nbdy on 20.12.20.
//

#ifndef PUI_BASEMODULE_H
#define PUI_BASEMODULE_H

#include <string>

enum ModuleTypes {
    UI = 0, BACKGROUND = 1
};

class BaseModule {
public:
    BaseModule();

    /*!
     * call this in the managers work function
     * @return false if something is wrong and the module should be stopped
     */
    virtual bool work();

    /*!
     * draw a widget representation of the module
     * @param x
     * @param y
     * @return true if the widget was clicked
     */
    virtual bool drawWidget(int x, int y);

    /*!
     * draw the module itself
     */
    virtual void drawModule();

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
};

extern "C" BaseModule* create();

#endif //PUI_BASEMODULE_H
