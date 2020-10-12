#include "gui/sdr_picker.h"

#include <sstream>

#include <glog/logging.h>

#include "gui/imgui_disable.h"
#include "gui/imgui_progress.h"
#include "util/stl_helper.h"

namespace sna {
namespace {
void DebugPrintDeviceList(const SoapySDR::KwargsList& device_list) {
  int i = 0;
  for (const auto& device : device_list) {
    LOG(INFO) << "Device " << ++i;
    for (const auto& [key, value] : device) {
      LOG(INFO) << "\t" << key << "=" << value;
    }
  }
}
}  // namespace
SdrPicker::SdrPicker() : ImGuiWindow("Device List", true, false) {
  using namespace std::placeholders;
  RegisterEventHandler<Event::DevicesEnumerated, DevicesEnumeratedEvent>(
      std::bind(&SdrPicker::OnDevicesEnumerated, this, _1));

  EnumerateDevices();
}  // namespace sna

void SdrPicker::OnDraw() {
  {
    ImGui::ScopedDisable scoped_disable{pending_enumerate_};

    if (ImGui::Button("Refresh")) {
      EnumerateDevices();
    }
    ImGui::SameLine();

    std::vector<const char*> combo_items;
    for (const auto& str : device_desc_)
      combo_items.push_back(str.c_str());
    ImGui::Combo("Devices", &selected_device_idx_, combo_items.data(),
                 (int)combo_items.size());
  }
  if (pending_enumerate_) {
    ImGui::SameLine();
    const ImU32 col = ImGui::GetColorU32(ImGuiCol_ButtonHovered);
    ImGui::Spinner("##spinner", ImGui::GetTextLineHeight() / 2,
                   (int)ImGui::GetTextLineHeight() / 4, col);
  }
  ImGui::Separator();
  {
    ImGui::ScopedDisable scoped_disable{pending_enumerate_};
    if (!device_list_.empty()) {
      for (const auto& [key, value] : device_list_.at(selected_device_idx_)) {
        ImGui::InputText(key.c_str(), const_cast<char*>(value.c_str()),
                         value.length(), ImGuiInputTextFlags_ReadOnly);
      }
    } else {
      ImGui::Text("No device selected");
    }
  }
  ImGui::Separator();
  {
    ImGui::ScopedDisable scoped_disable(device_list_.empty());
    if (ImGui::Button("OK", ImVec2(120, 0))) {
      Dispatch(DeviceSelectedEvent(device_list_.at(selected_device_idx_)));
      ImGui::CloseCurrentPopup();
    }
  }
  ImGui::SetItemDefaultFocus();
  ImGui::SameLine();
  if (ImGui::Button("Cancel", ImVec2(120, 0))) {
    Dispatch(CancelledEvent());
    ImGui::CloseCurrentPopup();
  }
}

void SdrPicker::EnumerateDevices() {
  DCHECK(!pending_enumerate_);
  pending_enumerate_ = true;
  device_list_.clear();
  device_desc_.clear();
  selected_device_idx_ = 0;
  BeginDispatch(
      []() { return DevicesEnumeratedEvent(SoapySDR::Device::enumerate()); });
}

void SdrPicker::OnDevicesEnumerated(const DevicesEnumeratedEvent& e) {
  device_list_ = e.GetDevices();
  device_desc_.clear();
  selected_device_idx_ = 0;
  for (const auto& device : device_list_) {
    device_desc_.push_back(GetDeviceDescription(device));
  }
  pending_enumerate_ = false;

  DebugPrintDeviceList(device_list_);
}

std::string SdrPicker::GetDeviceDescription(const SoapySDR::Kwargs& device) {
  std::stringstream ss;
  ss << get_or(device, "label", "<unnamed device>") << " ("
     << get_or(device, "driver", "<no driver>") << ")";
  return ss.str();
}

}  // namespace sna