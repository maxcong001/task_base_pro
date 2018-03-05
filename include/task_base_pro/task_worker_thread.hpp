#pragma once

#include "util.hpp"
#include "events/dispatcher.h"

#include "events/dispatcher_impl.h"
class task_worker_thread 
{
  public:
    task_worker_thread() : dispatcher_(new DispatcherImpl()) {}
    ~task_worker_thread()
    {
        exit();
    }

    void start();

    Dispatcher &dispatcher() { return *dispatcher_; }

    void exit();

  private:
    void threadRoutine();

    DispatcherPtr dispatcher_;
    std::thread thread_;
};
using worker_ptr_t = std::shared_ptr<task_worker_thread>;
using worker_array = std::array<worker_ptr_t, MAX_WORKER_SIZE>;

