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
#ifndef _FCITX_MODULES_SPELL_SPELL_H_
#define _FCITX_MODULES_SPELL_SPELL_H_

#include "fcitx-config/configuration.h"
#include "fcitx-config/enum.h"
#include "fcitx-config/iniparser.h"
#include "fcitx-utils/i18n.h"
#include "fcitx/addonfactory.h"
#include "fcitx/addoninstance.h"
#include "fcitx/instance.h"
#include "spell_public.h"

namespace fcitx {

FCITX_CONFIG_ENUM_NAME(SpellProvider, "Presage", "Custom", "Enchant")
FCITX_CONFIG_ENUM_I18N_ANNOTATION(SpellProvider, N_("Presage"), N_("Custom"),
                                  N_("Enchant"));

struct NotEmptyProvider {
    bool check(const std::vector<SpellProvider> &providers) const {
        return !providers.empty();
    }
    void dumpDescription(RawConfig &) const {}
};

FCITX_CONFIGURATION(SpellConfig,
                    fcitx::Option<std::vector<SpellProvider>, NotEmptyProvider,
                                  DefaultMarshaller<std::vector<SpellProvider>>,
                                  SpellProviderI18NAnnotation>
                        providerOrder{this,
                                      "ProviderOrder",
                                      "Order of providers",
                                      {SpellProvider::Presage,
                                       SpellProvider::Custom,
                                       SpellProvider::Enchant}};);

class Spell;
class SpellBackend;

class Spell final : public AddonInstance {
public:
    Spell(Instance *instance);
    ~Spell();

    void reloadConfig() override;
    const Configuration *getConfig() const override { return &config_; }
    void setConfig(const RawConfig &config) override {
        config_.load(config, true);
        safeSaveAsIni(config_, "conf/spell.conf");
    }

    const SpellConfig &config() const { return config_; }
    Instance *instance() { return instance_; }

    bool checkDict(const std::string &language);
    void addWord(const std::string &language, const std::string &word);
    std::vector<std::string> hint(const std::string &language,
                                  const std::string &word, size_t limit);
    std::vector<std::string> hintWithProvider(const std::string &language,
                                              SpellProvider provider,
                                              const std::string &word,
                                              size_t limit);

private:
    FCITX_ADDON_EXPORT_FUNCTION(Spell, checkDict);
    FCITX_ADDON_EXPORT_FUNCTION(Spell, addWord);
    FCITX_ADDON_EXPORT_FUNCTION(Spell, hint);
    FCITX_ADDON_EXPORT_FUNCTION(Spell, hintWithProvider);
    SpellConfig config_;
    typedef std::unordered_map<SpellProvider, std::unique_ptr<SpellBackend>,
                               EnumHash>
        BackendMap;
    BackendMap backends_;

    BackendMap::iterator findBackend(const std::string &language);
    BackendMap::iterator findBackend(const std::string &language,
                                     SpellProvider provider);
    Instance *instance_;
};

class SpellBackend {
public:
    SpellBackend(Spell *spell) : parent_(spell) {}
    virtual ~SpellBackend() {}

    virtual bool checkDict(const std::string &language) = 0;
    virtual void addWord(const std::string &language,
                         const std::string &word) = 0;
    virtual std::vector<std::string> hint(const std::string &language,
                                          const std::string &word,
                                          size_t limit) = 0;

    const SpellConfig &config() { return parent_->config(); }

private:
    Spell *parent_;
};
} // namespace fcitx

#endif // _FCITX_MODULES_SPELL_SPELL_H_
