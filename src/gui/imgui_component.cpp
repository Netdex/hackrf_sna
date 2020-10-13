#include "gui/imgui_component.h"

#include <algorithm>

namespace sna {

void ImGuiComponent::Process() {
  ProcessEvents();
  for (const auto& child : children_) {
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

void ImGuiComponent::Finished() {
  Dispatch(ComponentFinishedEvent());
}

}  // namespace sna