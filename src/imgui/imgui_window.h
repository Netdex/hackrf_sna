#pragma once

#include <string>

#include "imgui/imgui_component.h"

namespace sna {

class ImGuiWindow : public ImGuiComponent {
 public:
  ImGuiWindow(std::string title,
              bool modal = false,
              bool closeable = true,
              ImGuiWindowFlags flags = ImGuiWindowFlags_None |
                                       ImGuiWindowFlags_AlwaysAutoResize);

  void Process() final override;

  void Show(bool visible = true) { p_open_ = visible; }

 private:
  std::string title_;
  bool modal_;
  bool closeable_;
  ImGuiWindowFlags flags_;

  bool p_open_ = true;
  bool open_modal_ = true;
};
}  // namespace sna