#pragma once

#include <functional>
#include <memory>
#include <thread>
#include <typeindex>

#include <eventpp/eventqueue.h>
#include <eventpp/utilities/eventmaker.h>
#include <glog/logging.h>

namespace sna {

class Event {
 public:
  virtual ~Event() = default;
};

class EventDispatcher {
  struct EventPolicy {
    static std::type_index getEvent(const std::unique_ptr<Event>& e) {
      return std::type_index(typeid(*e));
    }
  };

  using EventQueue = eventpp::EventQueue<std::type_index,
                                         void(const std::unique_ptr<Event>&),
                                         EventPolicy>;

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
    // Unnecessary copy in handler capture
    queue_.appendListener(std::type_index(typeid(TEvent)),
                          [handler](const std::unique_ptr<Event>& e) {
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