#pragma once

#include <string>

#include <imgui.h>

#include "util/event_dispatcher.h"

namespace sna {

class ImGuiWindow : public EventDispatcher {
 public:
  ImGuiWindow(std::string title,
              bool modal = false,
              bool closeable = true,
              ImGuiWindowFlags flags = ImGuiWindowFlags_None |
                                       ImGuiWindowFlags_AlwaysAutoResize);

  ImGuiWindow(const ImGuiWindow&) = delete;
  ImGuiWindow& operator=(const ImGuiWindow&) = delete;

  virtual void OnDraw() {}
  void Process();

  void Show(bool visible = true) { p_open_ = visible; }
  void ShowModal() const { ImGui::OpenPopup(title_.c_str()); }

 private:
  std::string title_;
  ImGuiWindowFlags flags_;
  bool modal_;
  bool closeable_;

  bool p_open_ = true;
};
}  // namespace sna