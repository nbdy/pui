//
// Created by nbdy on 01.01.21.
//

#include <libgpsmm.h>

#include <BaseModule/BaseModule.h>

class GPS : public BaseModule {
protected:
     gpsmm rec;

     std::mutex mtx;
     gps_data_t* lastPosition {};
     gps_data_t* currentPosition {};

public:
    GPS(): BaseModule("GPS", "Provides GPS functionalities", "0.1"), rec("localhost", DEFAULT_GPSD_PORT) {
        if(rec.stream(WATCH_ENABLE|WATCH_JSON)) setError("GPSd not running.");
    }

    ~GPS() override {
        mtx.lock();
        delete currentPosition;
        delete lastPosition;
        mtx.unlock();
    }

    bool work(void *data, const context &ctx) override {
        if(!rec.waiting(50000000)) return true;
        mtx.lock();
        lastPosition = currentPosition;
        auto r = (currentPosition = rec.read()) != nullptr;
        mtx.unlock();
        return r;
    }

    shareMap getShareMap() override {
        shareMap r;
        mtx.lock();
        r["lastPosition"] = lastPosition;
        r["currentPosition"] = currentPosition;
        mtx.unlock();
        return r;
    }
};

extern "C" tModule* create() {
    return dynamic_cast<GPS*>(new GPS);
};