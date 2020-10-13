#pragma once

#include "gui/imgui_dockspace.h"

namespace sna{

class SnaWorkspace : public ImGuiDockSpace{
    public:
    void OnDraw() override;
};
}