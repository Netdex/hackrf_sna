#pragma once

#include <SoapySDR/Device.hpp>

namespace sna::wrapper {

class DeviceDeleter {
 public:
  void operator()(SoapySDR::Device* device) {
    SoapySDR::Device::unmake(device);
  }
};

std::unique_ptr<SoapySDR::Device, DeviceDeleter> CreateDevice(
    const SoapySDR::Kwargs&);

}  // namespace sna::wrapper