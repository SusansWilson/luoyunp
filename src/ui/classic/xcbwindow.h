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
#ifndef _FCITX_UI_CLASSIC_XCBWINDOW_H_
#define _FCITX_UI_CLASSIC_XCBWINDOW_H_

#include "window.h"
#include "xcbui.h"
#include <cairo/cairo.h>
#include <xcb/xcb.h>

namespace fcitx {
namespace classicui {

class XCBWindow : public Window {
public:
    XCBWindow(XCBUI *ui, int width = 1, int height = 1);
    ~XCBWindow();

    void createWindow(xcb_visualid_t vid = 0, bool overrideRedirect = true);
    virtual void postCreateWindow() {}
    void destroyWindow();
    void resize(unsigned int width, unsigned int height) override;

    cairo_surface_t *prerender() override;
    void render() override;

    virtual bool filterEvent(xcb_generic_event_t *event) = 0;

protected:
    XCBUI *ui_;
    xcb_window_t wid_ = 0;
    xcb_colormap_t colorMap_ = 0;
    xcb_visualid_t vid_ = 0;
    std::unique_ptr<HandlerTableEntry<XCBEventFilter>> eventFilter_;
    std::unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)> surface_;
    std::unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)>
        contentSurface_;
};
}
}

#endif // _FCITX_UI_CLASSIC_XCBWINDOW_H_
