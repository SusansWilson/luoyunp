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

#include "fcitx-utils/log.h"
#include "fcitx/menu.h"

using namespace fcitx;

int main() {
    {
        auto menu = std::make_unique<Menu>();
        {
            SimpleAction a;
            menu->addAction(&a);
            FCITX_ASSERT(menu->actions().size() == 1);
        }
        FCITX_ASSERT(menu->actions().size() == 0);
        SimpleAction a2;
        menu->addAction(&a2);
        FCITX_ASSERT(menu->actions().size() == 1);
        menu.reset();
    }
    {
        auto menu = std::make_unique<Menu>();
        SimpleAction a;
        a.setMenu(menu.get());
        menu.reset();
        FCITX_ASSERT(a.menu() == nullptr);
    }
    return 0;
}
