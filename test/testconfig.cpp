/*
 * Copyright (C) 2015~2015 by CSSlayer
 * wengxt@gmail.com
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1 of the
 * License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; see the file COPYING. If not,
 * see <http://www.gnu.org/licenses/>.
 */

#include "testconfig.h"
#include "fcitx-utils/log.h"
#include <fcitx-config/configuration.h>
#include <fcitx-config/enum.h>
#include <fcitx-config/iniparser.h>
#include <vector>

int main() {
    TestConfig config;

    fcitx::I18NString str;
    str.set("A", "zh_CN");
    str.set("ABCD");
    config.i18nStringValue.setValue(str);
    fcitx::RawConfig rawConfig;
    config.save(rawConfig);

    fcitx::writeAsIni(rawConfig, stdout);

    FCITX_ASSERT(*rawConfig.valueByPath("IntOption") == "0");

    config.intValue.setValue(5);
    FCITX_ASSERT(config.intValue.value() == 5);
    // violates constrain
    config.intValue.setValue(20);
    // still have the old value
    FCITX_ASSERT(config.intValue.value() == 5);
    rawConfig.setValueByPath("EnumOption", "EnumB");

    config.subConfigValue.mutableValue()->intValue.setValue(5);
    FCITX_ASSERT(*config.subConfigValue->intValue == 5);

    FCITX_INFO() << rawConfig;
    config.load(rawConfig);
    FCITX_ASSERT(config.intValue.value() == 0);
    FCITX_ASSERT(config.enumValue.value() == TestEnum::EnumB);

    FCITX_ASSERT(config.i18nStringValue.value().match("") == "ABCD");
    FCITX_ASSERT(config.i18nStringValue.value().match("zh_CN") == "A");

    fcitx::RawConfig rawDescConfig;
    config.dumpDescription(rawDescConfig);
    fcitx::writeAsIni(rawDescConfig, stdout);

    auto intOption = rawConfig.get("IntOption")->detach();
    FCITX_ASSERT(intOption);
    FCITX_ASSERT(intOption->value() == "0");
    FCITX_ASSERT(!rawConfig.get("IntOption"));
    FCITX_ASSERT(!intOption->parent());

    return 0;
}
