//
// Copyright (C) 2017~2017 by CSSlayer
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
#ifndef _TEST_TESTCONFIG_H_
#define _TEST_TESTCONFIG_H_

#include "fcitx-config/configuration.h"
#include "fcitx-config/enum.h"

FCITX_CONFIG_ENUM(TestEnum, EnumA, EnumB)

namespace my {
FCITX_CONFIG_ENUM(TestEnum, EnumA, EnumB, EnumC)

FCITX_CONFIGURATION(
    TestSubSubConfig, FCITX_OPTION(intValue, int, "IntOption", "Int Option", 1);
    FCITX_OPTION(keyValue, fcitx::Key, "KeyOption", "Key Option",
                 fcitx::Key(FcitxKey_A, fcitx::KeyState::Ctrl)););
} // namespace my

FCITX_CONFIGURATION(
    TestSubConfig,
    fcitx::Option<int> intValue{this, "IntOption", "Int Option", 1};
    fcitx::Option<fcitx::Key> keyValue{this, "KeyOption", "Key Option",
                                       fcitx::Key()};
    fcitx::Option<std::vector<my::TestSubSubConfig>> subSubVectorConfigValue{
        this, "SubSubConfig", "SubSubConfig Option", []() {
            std::vector<my::TestSubSubConfig> value;
            value.resize(2);
            value[0].intValue.setValue(2);
            value[0].keyValue.setValue(fcitx::Key("Alt+b"));
            return value;
        }()};);

FCITX_CONFIGURATION(
    TestConfig,
    fcitx::Option<int, fcitx::IntConstrain> intValue{
        this, "IntOption", "Int Option", 0, fcitx::IntConstrain(0, 10)};
    fcitx::Option<fcitx::Color> colorValue{this, "ColorOption", "Color Option",
                                           fcitx::Color()};
    fcitx::Option<bool> boolValue{this, "BoolOption", "Bool Option", true};
    fcitx::Option<std::string> stringValue{this, "StringOption",
                                           "String Option", "Test String"};
    fcitx::Option<TestEnum> enumValue{this, "EnumOption", "Enum Option",
                                      TestEnum::EnumA};
    fcitx::Option<std::vector<my::TestEnum>> enumVectorValue{
        this,
        "EnumVectorOption",
        "Enum Vector Option",
        {my::TestEnum::EnumA, my::TestEnum::EnumB}};
    fcitx::Option<std::vector<std::string>> stringVectorValue{
        this, "StringVectorOption", "String Option",
        std::vector<std::string>({"ABC", "CDE"})};
    fcitx::Option<std::vector<int>, fcitx::ListConstrain<fcitx::IntConstrain>>
        intVector{
            this, "IntVectorOption", "Int Vector", std::vector<int>{0},
            fcitx::ListConstrain<fcitx::IntConstrain>(fcitx::IntConstrain(0))};
    fcitx::Option<fcitx::I18NString> i18nStringValue{this, "I18NString",
                                                     "I18NString"};
    fcitx::Option<TestSubConfig> subConfigValue{this, "SubConfigOption",
                                                "SubConfig Option"};
    fcitx::ExternalOption ext{this, "ExternalOption", "ExternalOption",
                              "fcitx://config/addon/test/ext"};)

#endif // _TEST_TESTCONFIG_H_
