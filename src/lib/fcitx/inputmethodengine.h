//
// Copyright (C) 2016~2016 by CSSlayer
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
#ifndef _FCITX_INPUTMETHODENGINE_H_
#define _FCITX_INPUTMETHODENGINE_H_

#include "fcitxcore_export.h"
#include <fcitx/addoninstance.h>
#include <fcitx/event.h>
#include <fcitx/inputmethodentry.h>

namespace fcitx {

class FCITXCORE_EXPORT InputMethodEngine : public AddonInstance {
public:
    virtual ~InputMethodEngine() {}

    virtual std::vector<InputMethodEntry> listInputMethods() { return {}; }
    virtual void keyEvent(const InputMethodEntry &entry,
                          KeyEvent &keyEvent) = 0;
    // fcitx gurantee that activate and deactivate appear in pair for all input
    // context
    // activate means it will be used.
    virtual void activate(const InputMethodEntry &, InputContextEvent &) {}
    // deactivate means it will not be used for this context
    virtual void deactivate(const InputMethodEntry &entry,
                            InputContextEvent &event) {
        reset(entry, event);
    }
    // reset will only be called if ic is focused
    virtual void reset(const InputMethodEntry &, InputContextEvent &) {}
    virtual void filterKey(const InputMethodEntry &, KeyEvent &) {}
    virtual void updateSurroundingText(const InputMethodEntry &) {}
    virtual std::string subMode(const InputMethodEntry &, InputContext &) {
        return {};
    }
    virtual std::string overrideIcon(const InputMethodEntry &) { return {}; }
    virtual const Configuration *
    getConfigForInputMethod(const InputMethodEntry &) const {
        return getConfig();
    }
    virtual void setConfigForInputMethod(const InputMethodEntry &,
                                         const RawConfig &config) {
        setConfig(config);
    }
};
} // namespace fcitx

#endif // _FCITX_INPUTMETHODENGINE_H_
