#pragma once

#include <string>
#include <zmq.hpp>

namespace sna {
class SdrSource {
 public:
  SdrSource(zmq::context_t& context, std::string endpoint);

 private:
  zmq::socket_t socket_;
};

}  // namespace sna