#pragma once

#include <SoapySDR/Device.hpp>

#include "imgui/imgui_window.h"

namespace sna {

EVENTPP_MAKE_EVENT(DevicesEnumeratedEvent,
                   Event,
                   (),
                   (SoapySDR::KwargsList, GetDevices));
EVENTPP_MAKE_EVENT(DeviceSelectedEvent,
                   Event,
                   (),
                   (SoapySDR::Kwargs, GetDevice));

class DevicePicker : public ImGuiWindow {
 public:
  explicit DevicePicker();

  void Draw() override;

  void EnumerateDevices();
  void OnDevicesEnumerated(const DevicesEnumeratedEvent&);

 private:
  static std::string GetDeviceDescription(const SoapySDR::Kwargs&);

  SoapySDR::KwargsList device_list_;
  std::vector<std::string> device_desc_;
  int selected_device_idx_ = 0;
  bool pending_enumerate_ = false;
};

}  // namespace sna