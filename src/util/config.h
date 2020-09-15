#pragma once

#include <toml.hpp>

namespace sna {

toml::value& GetConfig();

void SaveConfig();

}  // namespace sna