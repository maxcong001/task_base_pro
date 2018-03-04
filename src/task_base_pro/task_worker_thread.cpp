#include "task_base_pro/task_worker_thread.hpp"


void task_worker_thread::start()
{
    thread_ = std::thread([this]() -> void { threadRoutine(); });
}

void task_worker_thread::exit()
{
    dispatcher_->exit();
    thread_.join();
}

void task_worker_thread::threadRoutine()
{
    dispatcher_->run(Dispatcher::RunType::Block);
    dispatcher_.reset();
}