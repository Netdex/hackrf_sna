
#pragma once

#include <eventpp/utilities/eventmaker.h>

namespace sna {

class Event {
 public:
  virtual ~Event() = default;
};

// Generic Events
EVENTPP_MAKE_EMPTY_EVENT(CancelledEvent, Event, ());

}  // namespace sna