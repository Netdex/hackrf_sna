#pragma once

#include <functional>
#include <memory>
#include <thread>

#include <eventpp/eventqueue.h>
#include <eventpp/utilities/eventmaker.h>
#include <glog/logging.h>

#include "util/event.h"

namespace sna {

class EventDispatcher {
  struct EventPolicy {
    static EventType getEvent(const std::unique_ptr<Event>& e) {
      return e->type;
    }
  };

  using EventQueue = eventpp::
      EventQueue<EventType, void(const std::unique_ptr<Event>&), EventPolicy>;

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
  template <typename TEvent, typename Handler>
  void RegisterEventHandler(Handler&& handler) {
    // Create a dummy instance to get the type ID. This is non-optimal for large
    // event structures, but event handlers should seldom be registered so it
    // should not be a big issue. Optimally, we would modify event structures to
    // store a static type for the event ID.
    EventType type = TEvent().type;
    // Unnecessary copy in handler capture
    queue_.appendListener(type, [handler](const std::unique_ptr<Event>& e) {
      // Call handler with unwrapped event
      handler(*dynamic_cast<const TEvent*>(e.get()));
    });
  }

  /**
   * @brief Queue an event for dispatch in the event queue.
   * This method is thread-safe.
   *
   * @tparam TEvent The type of the event derived from Event
   * @param event The event to queue for dispatch
   */
  template <typename TEvent>
  void Dispatch(TEvent&& event) {
    queue_.enqueue(static_cast<std::unique_ptr<Event>>(
        std::make_unique<TEvent>(std::forward<TEvent>(event))));
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
        [this](Functor&& invoker, Args&&... args) {
          // Perform thread-safe dispatch
          Dispatch(std::forward<Functor>(invoker)(std::forward<Args>(args)...));
        },
        std::forward<Functor>(invoker), std::forward<Args>(args)...)
        .detach();
  }

  void ProcessEvents() { queue_.process(); }

 private:
  EventQueue queue_;
};
}  // namespace sna