#include "radio/sdr_sink.h"

namespace sna {
SdrSink::SdrSink(zmq::context_t& context, std::string endpoint)
    : socket_(context, ZMQ_SUB) {
  socket_.connect(endpoint);
}

}  // namespace sna