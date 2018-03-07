#pragma once

#include "task_worker_thread.hpp"
#include "util.hpp"

class task_group_base
{
  public:
    task_group_base(std::uint32_t worker_num) : generator(), distribution(0, (worker_num - 1))
    {
        if (_worker_num > _worker_array.size())
        {
            // log here
            _worker_num = _worker_array.size();
        }
        _worker_num = worker_num;
        _worker_array.fill(nullptr);
        //_worker_array.swap(workers);
    }
    task_group_base(){};
    virtual ~task_group_base()
    {
    }
    bool init()
    {
        for (std::uint32_t i = 0; i < _worker_num; i++)
        {
            _worker_array.at(i) = std::make_shared<task_worker_thread>();
            _worker_array[i]->start();
        }
        return true;
    }
    bool add_worker(worker_ptr_t worker) { return true; }
    bool broadcast_msg(TASK_MSG &msg)
    {
        for (auto it : _worker_array)
        {
            send2one_worker(msg, it);
        }
        return true;
    }
    bool send2one_worker(TASK_MSG &msg)
    {
        int number = distribution(generator);
        send2one_worker(msg, _worker_array.at(number));
        return true;
    }

    virtual bool send2one_worker(TASK_MSG &msg, worker_ptr_t worker) = 0;

    GROUP_TYPE get_group_type()
    {
        return _type;
    }

    void set_group_type(GROUP_TYPE type)
    {
        _type = type;
    }
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution;

    worker_array _worker_array;
    GROUP_TYPE _type;
    std::uint32_t _worker_num;
};

class hellow_world_task_group : public task_group_base
{
  public:
    hellow_world_task_group(std::uint32_t worker_num) : task_group_base(worker_num)
    {
        set_group_type(GROUP_TYPE::HELLOWORLD);
    }
    //hellow_world_task_group() = delete;
    ~hellow_world_task_group() {}

    bool send2one_worker(TASK_MSG &msg, worker_ptr_t worker) override
    {
        worker->dispatcher().post([msg]() {
            std::cout << "get message with type : \t" << (unsigned int)msg.type;
            std::cout << "hello world from thread with id : " << std::this_thread::get_id() << std::endl;
        });
        return true;
    }
};

using group_ptr_t = std::shared_ptr<task_group_base>;
using group_array = std::array<group_ptr_t, (long unsigned int)GROUP_TYPE::GROUP_MAX>;
