/*
 * Copyright (C) 2016~2016 by CSSlayer
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
#ifndef _FCITX_UI_CLASSIC_XCBUI_H_
#define _FCITX_UI_CLASSIC_XCBUI_H_

#include "classicui.h"
#include "fcitx-utils/rect.h"

#undef None

namespace fcitx {
namespace classicui {

class XCBInputWindow;
class XCBTrayWindow;

enum class MultiScreenExtension { Randr, Xinerama, EXTNone };

enum class XCBHintStyle { Default, None, Medium, Slight, Full };

enum class XCBRGBA { Default, None, RGB, BGR, VRGB, VBGR };

struct XCBFontOption {
    int dpi = -1;
    bool antialias = true;
    XCBHintStyle hint = XCBHintStyle::Default;
    XCBRGBA rgba = XCBRGBA::Default;
};

class XCBUI : public UIInterface {
public:
    XCBUI(ClassicUI *parent, const std::string &name, xcb_connection_t *conn,
          int defaultScreen);
    ~XCBUI();

    ClassicUI *parent() const { return parent_; }
    const std::string &name() const { return name_; }
    xcb_connection_t *connection() const { return conn_; }
    xcb_ewmh_connection_t *ewmh() const { return ewmh_; }
    int defaultScreen() const { return defaultScreen_; }
    xcb_colormap_t colorMap() const { return colorMap_; }
    xcb_visualid_t visualId() const;
    void update(UserInterfaceComponent component,
                InputContext *inputContext) override;
    void updateCursor(InputContext *inputContext) override;
    void updateCurrentInputMethod(InputContext *inputContext) override;
    void suspend() override;
    void resume() override;
    void setEnableTray(bool) override;

    const auto &screenRects() { return rects_; }
    int dpiByPosition(int x, int y);
    int dpi(int dpi);
    const XCBFontOption &fontOption() const { return fontOption_; }

private:
    void refreshCompositeManager();
    void initScreen();
    void updateTray();

    ClassicUI *parent_;
    std::string name_;
    xcb_connection_t *conn_;
    xcb_ewmh_connection_t *ewmh_;
    int defaultScreen_;
    xcb_colormap_t colorMap_;
    std::unique_ptr<XCBInputWindow> inputWindow_;
    std::unique_ptr<XCBTrayWindow> trayWindow_;
    bool enableTray_ = false;

    std::string compMgrAtomString_;
    xcb_atom_t compMgrAtom_ = XCB_ATOM_NONE;
    xcb_window_t compMgrWindow_ = XCB_WINDOW_NONE;

    XCBFontOption fontOption_;
    int maxDpi_ = -1;
    MultiScreenExtension multiScreen_ = MultiScreenExtension::EXTNone;
    int xrandrFirstEvent_ = 0;

    std::vector<std::pair<Rect, int>> rects_;

    std::vector<std::unique_ptr<HandlerTableEntryBase>> eventHandlers_;
};

void addEventMaskToWindow(xcb_connection_t *conn, xcb_window_t wid,
                          uint32_t mask);
}
}

#endif // _FCITX_UI_CLASSIC_XCBUI_H_
