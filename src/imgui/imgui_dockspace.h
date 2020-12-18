#pragma once

#include "imgui/imgui_component.h"

namespace sna {
class ImGuiDockSpace : public ImGuiComponent {
 public:
  ImGuiDockSpace(bool fullscreen = true,
                 bool padding = false,
                 ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar,
                 ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None)
      : fullscreen_(fullscreen),
        padding_(padding),
        window_flags_(window_flags | ImGuiWindowFlags_NoDocking),
        dockspace_flags_(dockspace_flags) {}

  void Process() final override;

 private:
  bool fullscreen_;
  bool padding_;
  ImGuiWindowFlags window_flags_;
  ImGuiDockNodeFlags dockspace_flags_;
};
}  // namespace sna