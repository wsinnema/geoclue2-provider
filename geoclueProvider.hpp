#ifndef GEOCLUEPROVIDERHPP
#define GEOCLUEPROVIDERHPP

#include <memory>
#include <thread>
#include <signal.h>

#include <core/dbus/dbus.h>
#include <core/dbus/asio/executor.h>
#include <core/dbus/service.h>
#include <core/dbus/types/stl/string.h>
#include <core/dbus/types/object_path.h>
#include <core/dbus/object.h>
#include "position.h"
#include "geoclue2.h"
#include <atomic>

class ULSObject;
class GeoclueObject {

    private:
        std::shared_ptr<core::dbus::Object> obj;
        std::shared_ptr<core::dbus::Signal<org::freedesktop::Geoclue2::Client::LocationUpdated, std::tuple<core::dbus::types::ObjectPath, core::dbus::types::ObjectPath>>> luSignal;
        core::dbus::Bus::Ptr bus;
        std::shared_ptr<core::dbus::Service> service;
        std::shared_ptr<core::dbus::Object> client;
        std::shared_ptr<core::dbus::Object> GetClient();
        com::ubuntu::location::Position getPositionFromLocation(std::shared_ptr<core::dbus::Object> obj);
        com::ubuntu::location::Heading getHeadingFromLocation(std::shared_ptr<core::dbus::Object> obj);
        com::ubuntu::location::Velocity getVelocityFromLocation(std::shared_ptr<core::dbus::Object> obj);
        std::atomic<uint> status;

        void updateUsingLocationPath(core::dbus::types::ObjectPath op);
        void startClient();
        void stopClient();

        enum client_status {
            position = 1 << 0,
            heading = 1 << 1,
            velocity = 1 << 2
        };

    public:
        std::shared_ptr<ULSObject> uobj;
        GeoclueObject(std::shared_ptr<core::dbus::Object> obj, core::dbus::Bus::Ptr bus, std::shared_ptr<core::dbus::Service> gcService);

        void connectPropertyLocationChanged();
        void connectPositionChangedSignal();
        void prepareClient();
        void authorize();
        void startPositionUpdates();
        void stopPositionUpdates();
        void startVelocityUpdates();
        void stopVelocityUpdates();
        void startHeadingUpdates();
        void stopHeadingUpdates();
};
#endif // GEOCLUEPROVIDERHPP
