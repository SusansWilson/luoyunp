//
// Copyright (C) 2015~2017 by CSSlayer
// wengxt@gmail.com
//
// This library is free software; you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; either version 2.1 of the
// License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; see the file COPYING. If not,
// see <http://www.gnu.org/licenses/>.
//

#include "xcbmodule.h"
#include "config.h"
#include "fcitx/instance.h"
#include "fcitx/misc_p.h"

namespace fcitx {

XCBModule::XCBModule(Instance *instance) : instance_(instance) {
    reloadConfig();
    openConnection("");
}

void XCBModule::reloadConfig() { readAsIni(config_, "conf/xcb.conf"); }

void XCBModule::openConnection(const std::string &name_) {
    std::string name = name_;
    if (name.empty()) {
        auto env = getenv("DISPLAY");
        if (env) {
            name = env;
            mainDisplay_ = name;
        }
    }
    if (name.empty() || conns_.count(name)) {
        return;
    }

    try {
        auto iter = conns_.emplace(std::piecewise_construct,
                                   std::forward_as_tuple(name),
                                   std::forward_as_tuple(this, name));
        onConnectionCreated(iter.first->second);
    } catch (const std::exception &e) {
    }
}

void XCBModule::removeConnection(const std::string &name) {
    auto iter = conns_.find(name);
    if (iter == conns_.end()) {
        return;
    }
    onConnectionClosed(iter->second);
    conns_.erase(iter);
    FCITX_INFO() << "Disconnected from X11 Display " << name;
    if (name == mainDisplay_) {
        mainDisplay_.clear();
        if (instance_->quitWhenMainDisplayDisconnected()) {
            instance_->exit();
        }
    }
}

std::unique_ptr<HandlerTableEntry<XCBEventFilter>>
XCBModule::addEventFilter(const std::string &name, XCBEventFilter filter) {
    auto iter = conns_.find(name);
    if (iter == conns_.end()) {
        return nullptr;
    }
    return iter->second.addEventFilter(filter);
}

std::unique_ptr<HandlerTableEntry<XCBConnectionCreated>>
XCBModule::addConnectionCreatedCallback(XCBConnectionCreated callback) {
    auto result = createdCallbacks_.add(callback);

    for (auto &p : conns_) {
        auto &conn = p.second;
        callback(conn.name(), conn.connection(), conn.screen(),
                 conn.focusGroup());
    }
    return result;
}

std::unique_ptr<HandlerTableEntry<XCBConnectionClosed>>
XCBModule::addConnectionClosedCallback(XCBConnectionClosed callback) {
    return closedCallbacks_.add(callback);
}

xkb_state *XCBModule::xkbState(const std::string &name) {
    auto iter = conns_.find(name);
    if (iter == conns_.end()) {
        return nullptr;
    }
    return iter->second.xkbState();
}

XkbRulesNames XCBModule::xkbRulesNames(const std::string &name) {
    auto iter = conns_.find(name);
    if (iter == conns_.end()) {
        return {};
    }
    return iter->second.xkbRulesNames();
}

std::unique_ptr<HandlerTableEntry<XCBSelectionNotifyCallback>>
XCBModule::addSelection(const std::string &name, const std::string &atom,
                        XCBSelectionNotifyCallback callback) {
    auto iter = conns_.find(name);
    if (iter == conns_.end()) {
        return nullptr;
    }
    return iter->second.addSelection(atom, callback);
}

std::unique_ptr<HandlerTableEntryBase>
XCBModule::convertSelection(const std::string &name, const std::string &atom,
                            const std::string &type,
                            XCBConvertSelectionCallback callback) {

    auto iter = conns_.find(name);
    if (iter == conns_.end()) {
        return nullptr;
    }
    return iter->second.convertSelection(atom, type, callback);
}

void XCBModule::onConnectionCreated(XCBConnection &conn) {
    for (auto &callback : createdCallbacks_.view()) {
        callback(conn.name(), conn.connection(), conn.screen(),
                 conn.focusGroup());
    }
}

void XCBModule::onConnectionClosed(XCBConnection &conn) {
    for (auto &callback : closedCallbacks_.view()) {
        callback(conn.name(), conn.connection());
    }
}

xcb_atom_t XCBModule::atom(const std::string &name, const std::string &atom,
                           bool exists) {
    auto iter = conns_.find(name);
    if (iter == conns_.end()) {
        return XCB_ATOM_NONE;
    }
    return iter->second.atom(atom, exists);
}

xcb_ewmh_connection_t *XCBModule::ewmh(const std::string &name) {
    auto iter = conns_.find(name);
    if (iter == conns_.end()) {
        return nullptr;
    }
    return iter->second.ewmh();
}

class XCBModuleFactory : public AddonFactory {
public:
    AddonInstance *create(AddonManager *manager) override {
        return new XCBModule(manager->instance());
    }
};
} // namespace fcitx

FCITX_ADDON_FACTORY(fcitx::XCBModuleFactory);
