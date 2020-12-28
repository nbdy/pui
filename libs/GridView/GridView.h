//
// Created by nbdy on 27.12.20.
//

#ifndef PUI_GRIDVIEW_H
#define PUI_GRIDVIEW_H

#include <utility>

#include <BaseModule/BaseModule.h>

typedef std::vector<BaseModule*> BaseModules;

template<class M>
class GridView {
    BaseModules modules;
    Rectangle bounds;
    int itemsPerRow = 4;
    Vector2 shortcutSize;

public:
    GridView();
    GridView(Rectangle bounds, BaseModules modules, int itemsPerRow=4);
    ~GridView();

    virtual void loop(void* data);

    static Vector2 getShortcutSize(int width, int itemsPerRow);
};

template<class M>
GridView<M>::GridView(Rectangle bounds, BaseModules modules, int itemsPerRow): bounds(bounds), modules(std::move(modules)), itemsPerRow(itemsPerRow), shortcutSize(getShortcutSize(bounds.width, itemsPerRow)) {}

template<class M>
GridView<M>::GridView(): modules(), bounds({0, 0, SCREEN_WIDTH, SCREEN_HEIGHT}), shortcutSize(getShortcutSize(SCREEN_WIDTH, itemsPerRow)) {}

template<class M>
GridView<M>::~GridView() = default;

template<class M>
void GridView<M>::loop(void* data) {
    auto* mgr = (M*) data;

    auto nextBounds = Rectangle {bounds.x, bounds.y, shortcutSize.x, shortcutSize.y};

    for(auto& m : modules) {
        for(int _ = 0; _ < itemsPerRow; _++) {
            if(m->shortcutClicked(nextBounds , m->getName().c_str())) {
                mgr->setCurrentModule(m);
                return;
            }
        }
    }
}

template<class M>
Vector2 GridView<M>::getShortcutSize(int width, int itemsPerRow) {
    float r = width / itemsPerRow;
    return Vector2 {r, r};
}

#endif //PUI_GRIDVIEW_H
