
#pragma once

#include <eventpp/utilities/eventmaker.h>

#include <SoapySDR/Device.hpp>

namespace sna {

using EventType = int;

class Event {
 public:
  // Cross-Dispatch Event Table
  enum : EventType {
    // Generic
    Cancelled,

    // DevicePicker
    DevicesEnumerated,
    DeviceSelected,

    Count
  };

  Event(EventType type) : type(type) {}
  virtual ~Event() = default;

  EventType type;
};

EVENTPP_MAKE_EMPTY_EVENT(CancelledEvent, Event, Cancelled);

EVENTPP_MAKE_EVENT(DevicesEnumeratedEvent,
                   Event,
                   DevicesEnumerated,
                   (SoapySDR::KwargsList, GetDevices));
EVENTPP_MAKE_EVENT(DeviceSelectedEvent,
                   Event,
                   DeviceSelected,
                   (SoapySDR::Kwargs, GetDevice));

}  // namespace sna