#pragma once

#include <initializer_list>
#include <list>
#include <utility>

#include <imgui.h>

#include "util/event_dispatcher.h"

namespace sna {

EVENTPP_MAKE_EMPTY_EVENT(ComponentFinishedEvent, Event, ());

class ImGuiComponent : public EventDispatcher {
 public:
  ImGuiComponent() = default;
  virtual ~ImGuiComponent() = default;

  ImGuiComponent(const ImGuiComponent&) = delete;
  ImGuiComponent& operator=(const ImGuiComponent&) = delete;

  virtual void Process();
  virtual void Draw(){};

  void AddChild(std::shared_ptr<ImGuiComponent> child);
  void AddChildren(
      std::initializer_list<std::shared_ptr<ImGuiComponent>> children);
  void RemoveChild(std::shared_ptr<ImGuiComponent> child);

 protected:
  void Finish();

 private:
  // Use a list, since we mutate during iteration
  std::list<std::shared_ptr<ImGuiComponent>> children_;
};
}  // namespace sna
