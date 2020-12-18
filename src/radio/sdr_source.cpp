#include "radio/sdr_source.h"

namespace sna {
SdrSource::SdrSource(zmq::context_t& context,
                     std::string endpoint,
                     std::unique_ptr<sdr::Stream> stream) : endpoint_(endpoint) {
  (void)context;
  (void)endpoint;
  (void)stream;
}
void SdrSource::Run(zmq::context_t& context) {
  zmq::socket_t socket(context, ZMQ_REQ);
  socket.bind(endpoint_);
}

}  // namespace sna