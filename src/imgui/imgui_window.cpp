#include "imgui/imgui_window.h"

namespace sna {

ImGuiWindow::ImGuiWindow(std::string title,
                         bool modal,
                         bool closeable,
                         ImGuiWindowFlags flags)
    : title_(std::move(title)),
      modal_(modal),
      closeable_(closeable),
      flags_(flags) {}

void ImGuiWindow::Process() {
  ImGuiComponent::Process();
  if (!p_open_)
    return;
  if (modal_) {
    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    if (open_modal_) {
      ImGui::OpenPopup(title_.c_str());
      open_modal_ = false;
    }
    if (ImGui::BeginPopupModal(title_.c_str(), closeable_ ? &p_open_ : nullptr,
                               flags_)) {
      Draw();
      ImGui::EndPopup();
    }
  } else {
    if (ImGui::Begin(title_.c_str(), closeable_ ? &p_open_ : nullptr, flags_)) {
      Draw();
      ImGui::End();
    }
  }
}

}  // namespace sna