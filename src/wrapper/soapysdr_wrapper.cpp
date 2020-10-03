#include "wrapper/soapysdr_wrapper.h"

namespace sna::wrapper {

std::unique_ptr<SoapySDR::Device, DeviceDeleter> CreateDevice(
    const SoapySDR::Kwargs& args) {
  return std::unique_ptr<SoapySDR::Device, DeviceDeleter>(
      SoapySDR::Device::make(args));
}

};  // namespace sna::wrapper