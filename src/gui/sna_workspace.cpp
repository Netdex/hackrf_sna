#include "gui/sna_workspace.h"

#include "gui/device_picker.h"

namespace sna {

void SnaWorkspace::Draw() {
  if (ImGui::BeginMenuBar()) {
    if (ImGui::BeginMenu("File")) {
      if (ImGui::MenuItem("Exit", "ALT+F4")) {
        Finish();
      }
      // ShowExampleMenuFile();
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("View")) {
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Device")) {
      if (ImGui::MenuItem("Open Device")) {
        auto device_picker = std::make_shared<sna::DevicePicker>();
        device_picker->RegisterEventHandler<DeviceSelectedEvent>(
            [](const DeviceSelectedEvent& event) {
              LOG(INFO) << event.GetDevice().at("label");
            });
        AddChild(device_picker);
      }
      ImGui::Separator();
      ImGui::EndMenu();
    }
    ImGui::EndMenuBar();
  }
}
}  // namespace sna