
#include <chrono>
#include <cstdint>
#include <functional>
#include <mutex>
#include <string>
#include <vector>

#include "events/dispatcher_impl.h"
#include "events/timer_impl.h"

#include "event2/event.h"

DispatcherImpl::DispatcherImpl()
    : base_(event_base_new()), post_timer_(createTimer([this]() -> void { runPostCallbacks(); })), HB_timer_(createTimer([this]() -> void { HB_func(); }))
{
  // The dispatcher won't work as expected if libevent hasn't been configured to use threads.
  RELEASE_ASSERT(Global::initialized());
  HB_timer_->enableTimer(std::chrono::milliseconds(5000));
#if 0
  // catch sigine  ctrl+c
  int signo = SIGINT;
  struct event *sig_event = evsignal_new(base_.get(), signo, [](int signo, short events, void *arg)
                                         {
                                           __LOG(debug, "catch sigint");
                                         },
                                         NULL);
  evsignal_add(sig_event, NULL);
#endif
}

DispatcherImpl::~DispatcherImpl()
{
  //  exit();
}

TimerPtr DispatcherImpl::createTimer(TimerCb cb)
{

  return TimerPtr{new TimerImpl(*this, cb)};
}

void DispatcherImpl::exit() { event_base_loopexit(base_.get(), nullptr); }

void DispatcherImpl::post(std::function<void()> callback)
{
  bool do_post;
  {
    std::unique_lock<std::mutex> lock(post_lock_);
    do_post = post_callbacks_.empty();
    post_callbacks_.push_back(callback);
  }

  if (do_post)
  {
    post_timer_->enableTimer(std::chrono::milliseconds(0));
  }
}

void DispatcherImpl::run(RunType type)
{

  // Flush all post callbacks before we run the event loop. We do this because there are post
  // callbacks that have to get run before the initial event loop starts running. libevent does
  // not gaurantee that events are run in any particular order. So even if we post() and call
  // event_base_once() before some other event, the other event might get called first.
  runPostCallbacks();

  event_base_loop(base_.get(), type == RunType::NonBlock ? EVLOOP_NONBLOCK : 0);
}

void DispatcherImpl::runPostCallbacks()
{
  std::unique_lock<std::mutex> lock(post_lock_);
  while (!post_callbacks_.empty())
  {
    std::function<void()> callback = post_callbacks_.front();
    post_callbacks_.pop_front();

    lock.unlock();
    callback();
    lock.lock();
  }
}
