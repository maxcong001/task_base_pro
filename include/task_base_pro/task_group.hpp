#include "task_base_pro.hpp"

class task_group_base
{
  public:
    task_group_base(GROUP_TYPE type, std::uint32_t worker_num)
    {
        _worker_array.fill(nullptr);
    }
    virtual ~task_group_base()
    {
    }
    virtual void init() = 0;

    bool broad_cast_msg(TASK_MSG msg)
    {
    }

    worker_array _worker_array;
    GROUP_TYPE _type;
};

class manager_group : task_group_base
{

};
