/*
 * SPDX-FileCopyrightText: 2015-2015 CSSlayer <wengxt@gmail.com>
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 *
 */
#ifndef _FCITX_UTILS_DBUS_BUS_H_
#define _FCITX_UTILS_DBUS_BUS_H_

#include <string>
#include <vector>
#include <fcitx-utils/dbus/matchrule.h>
#include <fcitx-utils/dbus/message.h>
#include <fcitx-utils/dbus/objectvtable.h>
#include <fcitx-utils/event.h>

namespace fcitx {

namespace dbus {

class FCITXUTILS_EXPORT Slot {
public:
    virtual ~Slot();
};

enum class BusType { Default, Session, System };
enum class RequestNameFlag {
    ReplaceExisting = 1ULL << 0,
    AllowReplacement = 1ULL << 1,
    Queue = 1ULL << 2
};

class BusPrivate;

class FCITXUTILS_EXPORT Bus {
public:
    Bus(const std::string &address);
    Bus(BusType type);
    virtual ~Bus();
    Bus(const Bus &other) = delete;
    Bus(Bus &&other) noexcept;

    bool isOpen() const;

    void attachEventLoop(EventLoop *loop);
    void detachEventLoop();

    FCITX_NODISCARD std::unique_ptr<Slot> addMatch(const MatchRule &rule,
                                                   MessageCallback callback);
    FCITX_NODISCARD std::unique_ptr<Slot> addFilter(MessageCallback callback);
    FCITX_NODISCARD std::unique_ptr<Slot> addObject(const std::string &path,
                                                    MessageCallback callback);
    bool addObjectVTable(const std::string &path, const std::string &interface,
                         ObjectVTableBase &obj);

    Message createSignal(const char *path, const char *interface,
                         const char *member);
    Message createMethodCall(const char *destination, const char *path,
                             const char *interface, const char *member);

    void *nativeHandle() const;
    bool requestName(const std::string &name, Flags<RequestNameFlag> flags);
    bool releaseName(const std::string &name);

    std::string serviceOwner(const std::string &name, uint64_t usec);
    std::unique_ptr<Slot> serviceOwnerAsync(const std::string &name,
                                            uint64_t usec,
                                            MessageCallback callback);

    std::string uniqueName();
    std::string address();
    void flush();

private:
    std::unique_ptr<BusPrivate> d_ptr;
    FCITX_DECLARE_PRIVATE(Bus);
};
} // namespace dbus
} // namespace fcitx

#endif // _FCITX_UTILS_DBUS_BUS_H_
