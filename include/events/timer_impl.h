#pragma once

#include <chrono>

#include "timer.h"

#include "dispatcher_impl.h"
#include "event_impl_base.h"

/**
 * libevent implementation of Event::Timer.
 */
class TimerImpl : public Timer, ImplBase
{
public:
  TimerImpl(DispatcherImpl &dispatcher, TimerCb cb);

  void disableTimer() override;
  void enableTimer(const std::chrono::milliseconds &d) override;

private:
  TimerCb cb_;
};
