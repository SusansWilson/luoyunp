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
#ifndef _FCITX_UTILS_MISC_H_
#define _FCITX_UTILS_MISC_H_

#include <cstdint>
#include <fcitx-utils/macros.h>
#include <memory>
#include <utility>
#include <vector>

namespace fcitx {

template <class Parent, class Member>
inline std::ptrdiff_t
offsetFromPointerToMember(const Member Parent::*ptr_to_member) {
    const Parent *const parent = 0;
    const char *const member = static_cast<const char *>(
        static_cast<const void *>(&(parent->*ptr_to_member)));
    return std::ptrdiff_t(
        member - static_cast<const char *>(static_cast<const void *>(parent)));
}

template <class Parent, class Member>
inline Parent *parentFromMember(Member *member,
                                const Member Parent::*ptr_to_member) {
    return static_cast<Parent *>(
        static_cast<void *>(static_cast<char *>(static_cast<void *>(member)) -
                            offsetFromPointerToMember(ptr_to_member)));
}

template <class Parent, class Member>
inline const Parent *parentFromMember(const Member *member,
                                      const Member Parent::*ptr_to_member) {
    return static_cast<const Parent *>(static_cast<const void *>(
        static_cast<const char *>(static_cast<const void *>(member)) -
        offsetFromPointerToMember(ptr_to_member)));
}

template <typename Iter>
class KeyIterator {
public:
    typedef typename Iter::iterator_category iterator_category;
    typedef typename Iter::value_type::first_type value_type;
    typedef typename Iter::difference_type difference_type;
    typedef typename Iter::value_type::first_type &reference;
    typedef typename Iter::value_type::first_type *pointer;

    KeyIterator(Iter iter) : iter_(iter) {}
    FCITX_INLINE_DEFINE_DEFAULT_DTOR_AND_COPY(KeyIterator)

    bool operator==(const KeyIterator &other) const noexcept {
        return iter_ == other.iter_;
    }
    bool operator!=(const KeyIterator &other) const noexcept {
        return !operator==(other);
    }

    KeyIterator &operator++() {
        iter_++;
        return *this;
    }

    KeyIterator operator++(int) {
        auto old = iter_;
        ++(*this);
        return {old};
    }

    reference operator*() { return iter_->first; }

    pointer operator->() { return &iter_->first; }

private:
    Iter iter_;
};

template <typename It>
struct IterRange {
    It begin_, end_;
    It begin() const { return begin_; }
    It end() const { return end_; }
};

template <typename Iter>
IterRange<Iter> MakeIterRange(Iter begin, Iter end) {
    return {begin, end};
}

struct EnumHash {
    template <typename T>
    inline auto operator()(T const value) const {
        return std::hash<std::underlying_type_t<T>>()(
            static_cast<std::underlying_type_t<T>>(value));
    }
};

FCITXUTILS_EXPORT void startProcess(const std::vector<std::string> &args,
                                    const std::string &workingDirectory = {});
} // namespace fcitx

#endif // _FCITX_UTILS_MISC_H_
