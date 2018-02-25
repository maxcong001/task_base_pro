#include "task_base_pro.hpp"

class task_group
{
  public:
    task_group()
    {
        _worker_array.fill(nullptr);
    }


    bool broad_cast_msg(TASK_MSG msg)
    {

    }

    worker_array _worker_array;
    std::string _name;
};