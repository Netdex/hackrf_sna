#include "gui/sna_workspace.h"

#include "gui/device_picker.h"
#include "wrapper/soapysdr_wrapper.h"

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

              sdr::Device device(event.GetDevice());
              size_t rx_count =
                  device.GetChannelCount(sdr::Direction::kReceive);
              size_t tx_count =
                  device.GetChannelCount(sdr::Direction::kTransmit);
              LOG(INFO) << "rx=" << rx_count << ", tx=" << tx_count;
              for (size_t i = 0; i < rx_count; ++i) {
                auto kwargs =
                    device.GetChannelInfo(sdr::Direction::kReceive, i);
                for (const auto& [key, value] : kwargs) {
                  LOG(INFO) << key << "=" << value;
                }
              }
              for (size_t i = 0; i < tx_count; ++i) {
                auto kwargs =
                    device.GetChannelInfo(sdr::Direction::kTransmit, i);
                for (const auto& [key, value] : kwargs) {
                  LOG(INFO) << key << "=" << value;
                }
              }
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