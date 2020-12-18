#include "imgui/imgui_component.h"

#include <algorithm>
#include <functional>

namespace sna {

void ImGuiComponent::Process() {
  ProcessEvents();
  auto it = children_.begin();
  while (it != children_.end()) {
    auto& child = *it;
    ++it;
    child->Process();
  }
}

void ImGuiComponent::AddChild(std::shared_ptr<ImGuiComponent> child) {
  child->RegisterEventHandler<ComponentFinishedEvent>(
      [this, child](const ComponentFinishedEvent&) { RemoveChild(child); });
  children_.push_back(child);
}

void ImGuiComponent::AddChildren(
    std::initializer_list<std::shared_ptr<ImGuiComponent>> children) {
  std::for_each(children.begin(), children.end(),
                [this](const std::shared_ptr<ImGuiComponent>& child) {
                  AddChild(child);
                });
}

void ImGuiComponent::RemoveChild(std::shared_ptr<ImGuiComponent> child) {
  children_.erase(std::remove(children_.begin(), children_.end(), child),
                  children_.end());
}

void ImGuiComponent::Finish() {
  Dispatch(ComponentFinishedEvent());
}

}  // namespace sna