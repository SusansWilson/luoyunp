#ifndef WL_SUBSURFACE
#define WL_SUBSURFACE
#include "fcitx-utils/signals.h"
#include <memory>
#include <wayland-client.h>
namespace fcitx {
namespace wayland {
class WlSurface;
class WlSubsurface final {
public:
    static constexpr const char *interface = "wl_subsurface";
    static constexpr const wl_interface *const wlInterface =
        &wl_subsurface_interface;
    static constexpr const uint32_t version = 1;
    typedef wl_subsurface wlType;
    operator wl_subsurface *() { return data_.get(); }
    WlSubsurface(wlType *data);
    WlSubsurface(WlSubsurface &&other) noexcept = delete;
    WlSubsurface &operator=(WlSubsurface &&other) noexcept = delete;
    auto actualVersion() const { return version_; }
    void setPosition(int32_t x, int32_t y);
    void placeAbove(WlSurface *sibling);
    void placeBelow(WlSurface *sibling);
    void setSync();
    void setDesync();

private:
    static void destructor(wl_subsurface *);
    uint32_t version_;
    std::unique_ptr<wl_subsurface, decltype(&destructor)> data_;
};
static inline wl_subsurface *rawPointer(WlSubsurface *p) {
    return p ? static_cast<wl_subsurface *>(*p) : nullptr;
}
} // namespace wayland
} // namespace fcitx
#endif
