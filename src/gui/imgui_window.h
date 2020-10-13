#pragma once

#include <string>

#include "gui/imgui_component.h"

namespace sna {

class ImGuiWindow : public ImGuiComponent {
 public:
  ImGuiWindow(std::string title,
              bool modal = false,
              bool closeable = true,
              ImGuiWindowFlags flags = ImGuiWindowFlags_None |
                                       ImGuiWindowFlags_AlwaysAutoResize);

  ImGuiWindow(const ImGuiWindow&) = delete;
  ImGuiWindow& operator=(const ImGuiWindow&) = delete;

  void Process() override;

  void Show(bool visible = true) { p_open_ = visible; }
  void ShowModal() const { ImGui::OpenPopup(title_.c_str()); }

 private:
  std::string title_;
  bool modal_;
  bool closeable_;
  ImGuiWindowFlags flags_;

  bool p_open_ = true;
};
}  // namespace sna