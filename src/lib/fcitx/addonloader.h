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
#ifndef _FCITX_ADDONRESOLVER_H_
#define _FCITX_ADDONRESOLVER_H_

#include "fcitxcore_export.h"
#include <fcitx/addoninfo.h>
#include <fcitx/addoninstance.h>
#include <string>
#include <unordered_map>

namespace fcitx {

class AddonFactory;
class AddonManager;

typedef std::unordered_map<std::string, AddonFactory *> StaticAddonRegistry;

class FCITXCORE_EXPORT AddonLoader {
public:
    virtual ~AddonLoader();
    virtual std::string type() const = 0;
    virtual AddonInstance *load(const AddonInfo &info,
                                AddonManager *manager) = 0;
};
} // namespace fcitx

#endif // _FCITX_ADDONRESOLVER_H_
