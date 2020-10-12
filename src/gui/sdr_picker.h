#pragma once

#include <SoapySDR/Device.hpp>

#include "gui/imgui_window.h"

namespace sna {

class SdrPicker : public ImGuiWindow {
 public:
  explicit SdrPicker();

  virtual void OnDraw() override;

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