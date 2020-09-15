#include "config.h"

#include <glog/logging.h>

#include <fstream>

namespace sna {

namespace {
const std::string kConfigFilePath = "hackrf_sna.toml";
toml::value table_;
}  // namespace

toml::value& GetConfig() {
  if (table_.is_uninitialized()) {
    try {
      table_ = toml::parse(kConfigFilePath);
    } catch (const std::runtime_error& e) {
      LOG(WARNING) << e.what();
      table_ = toml::table{};
    } catch (const toml::syntax_error& e) {
      LOG(FATAL) << e.what();
    }
  }
  return table_;
}

void SaveConfig() {
  if (table_.is_uninitialized()) {
    return;
  }
  std::ofstream of{kConfigFilePath};
  CHECK(of);
  of << table_;
  of.close();
  CHECK(of);
}

}  // namespace sna