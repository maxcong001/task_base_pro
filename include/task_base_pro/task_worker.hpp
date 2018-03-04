#include "task_base_pro.hpp"

void evfdCallback(int fd, short event, void *args);
class task_worker_base
{
  public:
    task_worker_base() : _timer_mgr(_loop)
    {
        _evfd = -1;
    }
    virtual ~task_worker_base()
    {
        if (_evfd >= 0)
        {
            close(_evfd);
            _evfd = -1;
        }
    }

    bool init(bool new_thread)
    {
        _evfd = eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
        if (_evfd < 0)
        {
            __LOG(error, "!!!!!!!!create event fd fail!");
            return false;
        }
        __LOG(debug, "init task with ID :" << _evfd);
        // start eventfd server
        try
        {
            _event_server = std::make_shared<translib::EventFdServer>(_loop.ev(), _evfd, evfdCallback, this);
        }
        catch (std::exception &e)
        {
            __LOG(error, "!!!!!!!!!!!!exception happend when trying to create event fd server, info :" << e.what());
            return false;
        }
        on_before_loop();
        _loop.start(new_thread);
        on_after_loop();
        return true;
    }

    virtual void on_before_loop()
    {
    }
    virtual void on_after_loop()
    {
    }
    virtual bool restart()
    {

    }
    virtual bool run() = 0;
    virtual void on_message() = 0;
    //!!!!NOTE, please make sure your job use less time than heartbeat interval,
    // or we will consider the heart beat is lost!!!!!
    void process_msg(uint64_t num)
    {
        TASK_QUEUE _tmp_task_queue;
        //__LOG(debug, "task with id : " << _evfd << " receive message");
        {
            std::lock_guard<std::mutex> lck(mtx);
            // actually process all the messages
            swap(_task_queue, _tmp_task_queue);
        }
        while (_tmp_task_queue.size() != 0)
        {
            auto tmp = _tmp_task_queue.front();
            if (tmp.type == MSG_TYPE::MANAGER_HB_REQ)
            {
                if (_group_type == GROUP_TYPE::MANAGER)
                {
                    _tmp_task_queue.pop();
                    // this is manager task, should not receive the HB req message
                    __LOG(warn, "manager task receive hb req");
                    //on_message(tmp);
                    // this is task 0, do not send HB rsp
                    continue;
                }
                else
                {
                    _tmp_task_queue.pop();
                    // this is HB message, send rsp
                    __LOG(debug, "task : " << _name << " send HB response to task0");
                    TASK_HB_REQ_MSG req_msg = TASK_ANY_CAST<TASK_HB_REQ_MSG>(tmp.body);
                    TASK_HB_RSP_MSG rsp_msg;
                    rsp_msg.from_group = _group_type;
                    rsp_msg.from_index = _index;
                    task_manager::instance()->send(MSG_TYPE::MANAGER_HB_RSP, rsp_msg, req_msg.from_group, req_msg.from_index);
                    continue;
                }
            }

            on_message(tmp);
            _tmp_task_queue.pop();
        }
    }

    void in_queue(TASK_MSG msg)
    {
        std::lock_guard<std::mutex> lck(mtx);
        _task_queue.emplace(msg);
    }
    TASK_MSG out_queue()
    {
        std::lock_guard<std::mutex> lck(mtx);
        return _task_queue.pop(msg);
    }
    void set_index(std::uint32_t index)
    {
        _index = index;
    }
    std::uint32_t get_index()
    {
        return _index;
    }
    TASK_QUEUE _task_queue;
    // index in the group
    std::uint32_t _index;

    std::mutex mtx;
    int _evfd;
    // note: do not change the sequence of _loop and _event_server
    // _event_server should distructure first!!!!
    translib::Loop _loop;
    std::shared_ptr<translib::EventFdServer> _event_server;
    // timer.
    translib::TimerManager _timer_mgr;
    // group type
    GROUP_TYPE _group_type;
};