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

#include "text.h"
#include "fcitx-utils/utf8.h"
#include <tuple>
#include <vector>
namespace fcitx {

class TextPrivate {
public:
    TextPrivate() = default;
    FCITX_INLINE_DEFINE_DEFAULT_DTOR_AND_COPY(TextPrivate)

    std::vector<std::tuple<std::string, TextFormatFlags>> texts_;
    int cursor_ = -1;
};

Text::Text() : d_ptr(std::make_unique<TextPrivate>()) {}

Text::Text(const std::string &text, TextFormatFlags flag) : Text() {
    append(text, flag);
}

FCITX_DEFINE_DPTR_COPY_AND_DEFAULT_DTOR_AND_MOVE(Text)

void Text::clear() {
    FCITX_D();
    d->texts_.clear();
    setCursor();
}

int Text::cursor() const {
    FCITX_D();
    return d->cursor_;
}

void Text::setCursor(int pos) {
    FCITX_D();
    d->cursor_ = pos;
}

void Text::append(const std::string &str, TextFormatFlags flag) {
    FCITX_D();
    if (!utf8::validate(str)) {
        throw std::invalid_argument("Invalid utf8 string");
    }
    d->texts_.emplace_back(str, flag);
}

const std::string &Text::stringAt(int idx) const {
    FCITX_D();
    return std::get<std::string>(d->texts_[idx]);
}

TextFormatFlags Text::formatAt(int idx) const {
    FCITX_D();
    return std::get<TextFormatFlags>(d->texts_[idx]);
}

size_t Text::size() const {
    FCITX_D();
    return d->texts_.size();
}

std::string Text::toString() const {
    FCITX_D();
    std::string result;
    for (auto &p : d->texts_) {
        result += std::get<std::string>(p);
    }

    return result;
}

size_t Text::textLength() const {
    FCITX_D();
    size_t length = 0;
    for (auto &p : d->texts_) {
        length += std::get<std::string>(p).size();
    }

    return length;
}

std::string Text::toStringForCommit() const {
    FCITX_D();
    std::string result;
    for (auto &p : d->texts_) {
        if (!(std::get<TextFormatFlags>(p) & TextFormatFlag::DontCommit)) {
            result += std::get<std::string>(p);
        }
    }

    return result;
}
} // namespace fcitx
