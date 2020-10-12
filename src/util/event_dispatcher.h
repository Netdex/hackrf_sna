#pragma once

#include <functional>
#include <memory>
#include <thread>

#include <eventpp/eventqueue.h>
#include <eventpp/utilities/eventmaker.h>
#include <glog/logging.h>

#include "util/event.h"

namespace sna {

struct EventPolicy {
  static EventType getEvent(const std::unique_ptr<Event>& e) { return e->type; }
};

using EventQueue = eventpp::
    EventQueue<EventType, void(const std::unique_ptr<Event>&), EventPolicy>;

class EventDispatcher {
 public:
  virtual ~EventDispatcher() = default;

  /**
   * @brief Register an event and its respective handler
   *
   * @tparam type The integral event type
   * @tparam TEvent The event class derived from Event
   * @tparam Handler A functor type of void(const TEvent&)
   * @param handler A functor of type Handler
   */
  template <EventType type, typename TEvent, typename Handler>
  void RegisterEventHandler(Handler&& handler) {
    // Unnecessary copy in handler capture
    queue_.appendListener(type, [handler](const std::unique_ptr<Event>& e) {
      // Call handler with unwrapped event
      handler(*dynamic_cast<const TEvent*>(e.get()));
    });
  }

  template <typename TEvent>
  void Dispatch(const TEvent& event) {
    queue_.enqueue(
        static_cast<std::unique_ptr<Event>>(std::make_unique<TEvent>(event)));
  }

  /**
   * @brief Asynchronously execute and dispatch result
   *
   * @tparam Functor A functor type returning type derived from Event
   * @tparam Args Types of arguments to be passed to functor
   * @param invoker A functor of type Functor
   * @param args Arguments to be passed to functor
   */
  template <typename Functor, typename... Args>
  void BeginDispatch(Functor&& invoker, Args&&... args) {
    std::thread(
        [&queue = queue_](Functor&& invoker, Args&&... args) {
          // Invoke functor and obtain event
          auto event =
              std::forward<Functor>(invoker)(std::forward<Args>(args)...);
          // Enqueue event wrapped in std::unique_ptr<Event>
          queue.enqueue(static_cast<std::unique_ptr<Event>>(
              std::make_unique<decltype(event)>(std::move(event))));
        },
        std::forward<Functor>(invoker), std::forward<Args>(args)...)
        .detach();
  }

  void ProcessEvents() { queue_.process(); }

 private:
  EventQueue queue_;
};
}  // namespace sna