//
// Copyright (C) 2015~2015 by CSSlayer
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
#ifndef _FCITX_ADDON_H_
#define _FCITX_ADDON_H_

#include "fcitxcore_export.h"
#include <fcitx-config/enum.h>
#include <fcitx-utils/i18nstring.h>
#include <fcitx-utils/macros.h>
#include <memory>
#include <vector>

namespace fcitx {

class AddonInfoPrivate;

FCITX_CONFIG_ENUM(AddonCategory, InputMethod, Frontend, Loader, Module, UI)

enum class OverrideEnabled { NotSet, Enabled, Disabled };

class FCITXCORE_EXPORT AddonInfo {
public:
    AddonInfo(const std::string &name);
    virtual ~AddonInfo();

    bool isValid() const;
    const std::string &uniqueName() const;
    const I18NString &name() const;
    const I18NString &comment() const;
    const std::string &type() const;
    AddonCategory category() const;
    const std::string &library() const;
    const std::vector<std::string> &dependencies() const;
    const std::vector<std::string> &optionalDependencies() const;
    bool onDemand() const;
    int uiPriority() const;
    bool isEnabled() const;
    bool isDefaultEnabled() const;
    void setOverrideEnabled(OverrideEnabled overrideEnabled);
    bool isConfigurable() const;

    void load(const RawConfig &config);

private:
    std::unique_ptr<AddonInfoPrivate> d_ptr;
    FCITX_DECLARE_PRIVATE(AddonInfo);
};
} // namespace fcitx

#endif // _FCITX_ADDON_H_
