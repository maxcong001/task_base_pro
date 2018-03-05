#pragma once

#include <cstdint>
#include <functional>
#include <list>
#include <mutex>
#include <vector>

#include "event2/event.h"

#include "events/libevent.h"

#include "events/dispatcher.h"
#include "events/timer.h"
/**
 * libevent implementation of Dispatcher.
 */
class DispatcherImpl : public Dispatcher
{
public:
  DispatcherImpl();
  ~DispatcherImpl();

  /**
   * @return event_base& the libevent base.
   */
  event_base &base() { return *base_; }

  TimerPtr createTimer(TimerCb cb) override;

  void exit() override;

  void post(std::function<void()> callback) override;
  void run(RunType type) override;

private:
  void runPostCallbacks();

  BasePtr base_;

  TimerPtr post_timer_;

  std::mutex post_lock_;
  std::list<std::function<void()>> post_callbacks_;
};
