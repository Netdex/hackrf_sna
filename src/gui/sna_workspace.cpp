#include "gui/sna_workspace.h"

namespace sna {
void SnaWorkspace::OnDraw() {
  if (ImGui::BeginMenuBar()) {
    if (ImGui::BeginMenu("File")) {
      if (ImGui::MenuItem("Exit", "ALT+F4")) {
        Dispatch(CancelledEvent());
      }
      // ShowExampleMenuFile();
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Edit")) {
      if (ImGui::MenuItem("Undo", "CTRL+Z")) {
      }
      if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {
      }  // Disabled item
      ImGui::Separator();
      if (ImGui::MenuItem("Cut", "CTRL+X")) {
      }
      if (ImGui::MenuItem("Copy", "CTRL+C")) {
      }
      if (ImGui::MenuItem("Paste", "CTRL+V")) {
      }
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