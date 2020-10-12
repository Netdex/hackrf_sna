#pragma once

#include <imgui.h>
#include <imgui_internal.h>

namespace ImGui {

void PushDisable() {
  ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
  ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.1f);
}

void PopDisable() {
  ImGui::PopItemFlag();
  ImGui::PopStyleVar();
}

class ScopedDisable {
 public:
  explicit ScopedDisable(bool disable = true) : disable_(disable) {
    if (disable_){
      PushDisable();
    }
  }

  ~ScopedDisable() {
    if (disable_){
      PopDisable();
    }
  }

  ScopedDisable(const ScopedDisable&) = delete;
  ScopedDisable& operator=(const ScopedDisable&) = delete;

 private:
  bool disable_;
};

}  // namespace ImGui