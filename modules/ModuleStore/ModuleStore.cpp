//
// Created by nbdy on 04.01.21.
//

#include <BaseModule/BaseModule.h>

class ModuleStore : public BaseModule {
public:
    ModuleStore(): BaseModule("ModuleStore", "(Down/Un)Load Modules", "0.1", "ModuleStore", UI, false) {}

    void loop(void *data) override {

    }

    bool work(void *data, const context &ctx) override {
        return true;
    }
};