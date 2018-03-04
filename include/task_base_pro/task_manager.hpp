#include "util.hpp"

using task_ptr_t = std::shared_ptr<task_worker_base>;
class task_manager
{
  public:
    task_manager()
    {
        _groups.fill(nullptr);
    }
    static task_manager *instance()
    {
        static task_manager *ins = new task_manager();
        return ins;
    }
    bool send(MSG_TYPE type, TASK_ANY body, GROUP_TYPE group, std::uint32_t index = 0xffffffff)
    {
    }
    bool refresh()
    {
    }
    std::uint32_t add_group(std::initializer_list<group_ptr_t> groups)
    {
        for (auto it : groups)
        {
            if (it)
            {
                try
                {
                    _groups.at(it->get_group_type()) = it;
                }
                catch (const std::out_of_range &e)
                {
                    // the group type is out of range
                    __LOG(error, "group type is invaliade!!!!");
                    // do not exit here,
                    // just continue
                    continue;
                }
            }
            else
            {
                __LOG(warn, "the group ptr is not ready");
            }
        }
    }
    bool del_group(GROUP_TYPE group)
    {
        return true;
    }

    bool init(bool _poll = true)
    {

        return true;
    }
    group_array _groups;
};