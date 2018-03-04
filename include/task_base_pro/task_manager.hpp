#pragma once
#include "util.hpp"
#include "task_group.hpp"

typedef std::function<void()> post_callback;
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
    bool post(GROUP_TYPE type, TASK_MSG msg)
    {
        // get group ptr_t
        try
        {
            auto group_ptr_t = _groups.at((unsigned int)type);
            // post message
            group_ptr_t->send2one_worker(msg);
        }
        catch (const std::out_of_range &oor)
        {
            // out of group range
            //std::cerr << "Out of Range error: " << oor.what() << '\n';
            return false;
        }
        return true;
    }

    bool add_group(group_array groups)
    {
        for (auto it : groups)
        {
            if (it)
            {
                add_group(it);
            }
            else
            {
                __LOG(warn, "the group ptr is not ready");
                return false;
            }
        }
        return true;
    }
    bool add_group(group_ptr_t group)
    {
        try
        {
            _groups.at((unsigned int)(group->get_group_type())) = group;
        }
        catch (const std::out_of_range &e)
        {
            // the group type is out of range
            __LOG(error, "group type is invaliade!!!!");

            return false;
        }
        return true;
    }
    bool del_group(GROUP_TYPE type)
    {
        return true;
    }

    bool init(bool _poll = true)
    {

        return true;
    }
    group_array _groups;
};