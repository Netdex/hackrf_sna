#pragma once

#include <functional>

#include "gui/imgui_component.h"

namespace sna {
class ImGuiFunctor : public ImGuiComponent {
 public:
  ImGuiFunctor(std::function<void(ImGuiFunctor&)> functor) : functor_(functor) {}

  void Process() override {
    ImGuiComponent::Process();
    Draw();
  }

  void Draw() override { functor_(*this); }

 private:
  std::function<void(ImGuiFunctor&)> functor_;
};
}  // namespace sna