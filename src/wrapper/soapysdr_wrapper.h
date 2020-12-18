#pragma once

#include <memory>

#include <glog/logging.h>
#include <SoapySDR/Device.hpp>
#include <SoapySDR/Formats.hpp>

// Introduce a level of indirection with SoapySDR API using idiomatic C++, for
// resilience against API changes.
namespace sna::sdr {

enum class Direction : int { kTransmit = 0, kReceive = 1 };
using Channel = size_t;

class Stream {
 public:
  ~Stream() { device_->closeStream(stream_); }

 private:
  Stream(std::shared_ptr<SoapySDR::Device> device,
         Direction dir,
         std::string format,
         std::vector<Channel> channels = std::vector<Channel>(),
         SoapySDR::Kwargs args = SoapySDR::Kwargs())
      : device_(device),
        stream_(device_->setupStream(static_cast<int>(dir),
                                     std::move(format),
                                     std::move(channels),
                                     std::move(args))) {}

  Stream(const Stream&) = delete;
  Stream& operator=(const Stream&) = delete;

  void Activate(int flags = 0, long long timeNs = 0, size_t numElems = 0) {
    int err = device_->activateStream(stream_, flags, timeNs, numElems);
    CHECK_EQ(err, 0);
  }

  void Deactivate(int flags = 0, long long timeNs = 0) {
    int err = device_->deactivateStream(stream_, flags, timeNs);
    CHECK_EQ(err, 0);
  }

  friend class Device;

  std::shared_ptr<SoapySDR::Device> device_;
  SoapySDR::Stream* stream_;
};

class Device {
 public:
  explicit Device(const SoapySDR::Kwargs& args)
      : device_(std::shared_ptr<SoapySDR::Device>(SoapySDR::Device::make(args),
                                                  DeviceDeleter())) {}

  size_t GetChannelCount(Direction dir) {
    return device_->getNumChannels(static_cast<int>(dir));
  }

  SoapySDR::Kwargs GetChannelInfo(Direction dir, Channel ch) {
    return device_->getChannelInfo(static_cast<int>(dir), ch);
  }

 private:
  struct DeviceDeleter {
    void operator()(SoapySDR::Device* device) {
      SoapySDR::Device::unmake(device);
    }
  };

  std::shared_ptr<SoapySDR::Device> device_;
};

}  // namespace sna::sdr
