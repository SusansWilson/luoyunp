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
#ifndef _FCITX_TEXT_H_
#define _FCITX_TEXT_H_

#include "fcitxcore_export.h"
#include <fcitx-utils/flags.h>
#include <fcitx-utils/macros.h>
#include <fcitx-utils/textformatflags.h>
#include <memory>
#include <string>

/// \addtogroup FcitxCore
/// \{
/// \file
/// \brief Formatted string commonly used in user interface.

namespace fcitx {
class TextPrivate;

/// A class represents a formatted string.
class FCITXCORE_EXPORT Text {
public:
    Text();
    explicit Text(const std::string &text,
                  TextFormatFlags flag = TextFormatFlag::None);
    FCITX_DECLARE_VIRTUAL_DTOR_COPY_AND_MOVE(Text);

    /// Get cursor by byte.
    int cursor() const;
    /// Set cursor by byte.
    void setCursor(int pos = -1);
    void clear();
    void append(const std::string &str,
                TextFormatFlags flag = TextFormatFlag::None);
    const std::string &stringAt(int idx) const;
    TextFormatFlags formatAt(int idx) const;
    size_t size() const;
    size_t textLength() const;
    std::string toString() const;
    std::string toStringForCommit() const;

private:
    std::unique_ptr<TextPrivate> d_ptr;
    FCITX_DECLARE_PRIVATE(Text);
};
} // namespace fcitx

#endif // _FCITX_TEXT_H_
