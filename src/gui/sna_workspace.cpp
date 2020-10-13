#include "gui/sna_workspace.h"

namespace sna {
void SnaWorkspace::Draw() {
  if (ImGui::BeginMenuBar()) {
    if (ImGui::BeginMenu("File")) {
      if (ImGui::MenuItem("Exit", "ALT+F4")) {
        Dispatch(CancelledEvent());
      }
      // ShowExampleMenuFile();
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("View")) {
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Device")) {
      if (ImGui::MenuItem("Open Device")) {
          
      }
      ImGui::Separator();
      ImGui::EndMenu();
    }
    ImGui::EndMenuBar();
  }
}
}  // namespace sna