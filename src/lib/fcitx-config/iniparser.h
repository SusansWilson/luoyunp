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
#ifndef _FCITX_CONFIG_INIPARSER_H_
#define _FCITX_CONFIG_INIPARSER_H_

#include "fcitxconfig_export.h"
#include <fcitx-config/rawconfig.h>

namespace fcitx {
class Configuration;
FCITXCONFIG_EXPORT void readFromIni(RawConfig &config, int fd);
FCITXCONFIG_EXPORT bool writeAsIni(const RawConfig &config, int fd);
FCITXCONFIG_EXPORT void readFromIni(RawConfig &config, FILE *fin);
FCITXCONFIG_EXPORT bool writeAsIni(const RawConfig &config, FILE *fout);
FCITXCONFIG_EXPORT void readAsIni(Configuration &, const std::string &name);
FCITXCONFIG_EXPORT void readAsIni(RawConfig &, const std::string &name);
FCITXCONFIG_EXPORT bool safeSaveAsIni(const Configuration &,
                                      const std::string &name);
FCITXCONFIG_EXPORT bool safeSaveAsIni(const RawConfig &,
                                      const std::string &name);
} // namespace fcitx

#endif // _FCITX_CONFIG_INIPARSER_H_
