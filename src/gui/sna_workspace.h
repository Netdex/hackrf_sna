#pragma once

#include "imgui/imgui_dockspace.h"

namespace sna {

class SnaWorkspace : public ImGuiDockSpace {
 public:
  void Draw() override;
};
}  // namespace sna