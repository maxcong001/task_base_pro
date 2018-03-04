#include "task_base_pro.hpp"

class task_group_base
{
  public:
    task_group_base(GROUP_TYPE type, std::initializer_list<worker_ptr_t> worker)//std::uint32_t worker_num)
    {
        _worker_array.fill(nullptr);
    }
    task_group_base() = delete;
    virtual ~task_group_base()
    {
    }
    virtual void init() = 0;

    bool broad_cast_msg(TASK_MSG msg)
    {
    }
    GROUP_TYPE get_group_type()
    {
        return _type;
    }

    worker_array _worker_array;
    GROUP_TYPE _type;
};

class manager_group : task_group_base
{
  public:
    manager_group(GROUP_TYPE type, std::uint32_t worker_num) : task_group_base(type, worker_num)
    {
    }
    manager_group() = delete;
    ~manager_group() {}

    bool add_worker(worker_ptr_t worker)
    {

    }
};
