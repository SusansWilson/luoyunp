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
#ifndef _FCITX_ADDONLOADER_P_H_
#define _FCITX_ADDONLOADER_P_H_

#include "addonfactory.h"
#include "addoninfo.h"
#include "addoninstance.h"
#include "addonloader.h"
#include "fcitx-utils/library.h"
#include "fcitx-utils/standardpath.h"
#include <exception>

namespace fcitx {

class SharedLibraryFactory {
public:
    SharedLibraryFactory(Library lib) : library_(std::move(lib)) {
        auto funcPtr = library_.resolve("fcitx_addon_factory_instance");
        if (!funcPtr) {
            throw std::runtime_error(library_.error());
        }
        auto func = Library::toFunction<AddonFactory *()>(funcPtr);
        factory_ = func();
        if (!factory_) {
            throw std::runtime_error("Failed to get a factory");
        }
    }

    AddonFactory *factory() { return factory_; }

private:
    Library library_;
    AddonFactory *factory_;
};

class SharedLibraryLoader : public AddonLoader {
public:
    ~SharedLibraryLoader();
    AddonInstance *load(const AddonInfo &info, AddonManager *manager) override;

    std::string type() const override { return "SharedLibrary"; }

private:
    StandardPath standardPath_;
    std::unordered_map<std::string, std::unique_ptr<SharedLibraryFactory>>
        registry_;
};

class StaticLibraryLoader : public AddonLoader {
public:
    StaticLibraryLoader(StaticAddonRegistry *registry_);

    AddonInstance *load(const AddonInfo &info, AddonManager *manager) override;

    std::string type() const override { return "StaticLibrary"; }

    StaticAddonRegistry *registry;
};
} // namespace fcitx

#endif // _FCITX_ADDONLOADER_P_H_
