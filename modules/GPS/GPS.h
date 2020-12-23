//
// Created by nbdy on 23.12.20.
//

#ifndef PUI_GPS_H
#define PUI_GPS_H

#include <BaseModule/BaseModule.h>

class GPS : public BaseModule {
public:
    GPS(): type(BACKGROUND), sharing(true), name("GPS"), description("Provides GPS functionalities"), version("0.1") {

    }
};

#endif //PUI_GPS_H
