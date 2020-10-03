#include "radio/sdr_source.h"

namespace sna {
SdrSource::SdrSource(zmq::context_t& context, std::string endpoint)
    : socket_(context, ZMQ_PUB) {
  socket_.bind(endpoint);
}

}  // namespace sna