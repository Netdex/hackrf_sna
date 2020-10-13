#pragma once

#include <imgui.h>

#include "util/event_dispatcher.h"

namespace sna {
class ImGuiComponent : public EventDispatcher {
 public:
  virtual ~ImGuiComponent() = default;

  virtual void OnDraw() {}
  virtual void Process() { ProcessEvents(); }
};
}  // namespace sna
