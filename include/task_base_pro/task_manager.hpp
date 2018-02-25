#include "util.hpp"

using task_ptr_t = std::shared_ptr<task_worker_base>;
class task_manager
{
  public:
    task_manager()
    {
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

    std::uint32_t add_group (GROUP_TYPE group, task_ptr_t task, std::uint32_t task_num)
    {

    }
    bool del_group(GROUP_TYPE group)
    {
   
        return true;
    }


    // note  if _poll is set to true, it will hang here and wait for incoming message
    bool init(bool _poll = true)
    {
        // add task0
        //std::shared_ptr<task_base> tmp_task_ptr_t = std::shared_ptr<manager_task>(new manager_task(std::string(TASK0)));
        task_ptr_t tmp_task_ptr_t = std::static_pointer_cast<task_base>(std::make_shared<manager_task>(std::string(TASK0)));
        add_tasks(tmp_task_ptr_t);

        if (task_map.find(TASK0) == task_map.end())
        {
            __LOG(error, "!!!!!!!!!at lease task0 should be provided!!");
            return false;
        }

        for (auto it : task_map)
        {
            if (!it.first.compare(TASK0))
            {
            }
            else
            {
                // this is not task 0, start a new task
                it.second->init(true);
            }
        }
        // init the task0
        if (_poll)
        {
            task_map[TASK0]->set_hb_interval(_hb_itval);
            task_map[TASK0]->init(false);
        }
        else
        {
            task_map[TASK0]->set_hb_interval(_hb_itval);
            task_map[TASK0]->init(true);
        }

        return true;
    }
    void set_hb_interval(std::uint32_t _hb_itval)
    {
        _hb_itval = _hb_itval;
        task_map[TASK0]->set_hb_interval(_hb_itval);
    }
    std::map<std::string, task_ptr_t> task_map;
    // heart beat interval
    std::uint32_t _hb_itval;
    std::atomic<std::uint32_t> _seq_id;
};