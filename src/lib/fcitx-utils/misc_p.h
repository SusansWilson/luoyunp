//
// Copyright (C) 2016~2020 by CSSlayer
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
#ifndef _FCITX_UTILS_MISC_P_H_
#define _FCITX_UTILS_MISC_P_H_

#include <string>
#include <type_traits>

namespace fcitx {

template <typename M, typename K>
decltype(&std::declval<M>().begin()->second) findValue(M &&m, K &&key) {
    auto iter = m.find(key);
    if (iter != m.end()) {
        return &iter->second;
    }
    return nullptr;
}

} // namespace fcitx

#endif // _FCITX_UTILS_MISC_P_H_
