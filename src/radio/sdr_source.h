#pragma once

#include <string>
#include <zmq.hpp>

#include "wrapper/soapysdr_wrapper.h"

namespace sna {
class SdrSource {
 public:
  SdrSource(zmq::context_t& context,
            std::string endpoint,
            std::unique_ptr<sdr::Stream> stream);

 private:
  void Run(zmq::context_t& context);

  std::string endpoint_;
};

}  // namespace sna