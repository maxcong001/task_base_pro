
#include "logger/logger.hpp"
#include "events/include"
#include "task_base_pro/include"
int main()
{
    set_log_level(logger_iface::log_level::warn);
    set_max_log_buff(10);
    for (int i = 0; i < 100; i++)
    {
        __LOG(error, "hello logger!"
                         << "this is error log");
        __LOG(warn, "hello logger!"
                        << "this is warn log");
        __LOG(info, "hello logger!"
                        << "this is info log");
        __LOG(debug, "hello logger!"
                         << "this is debug log");
    }
    dump_log();

    auto ins = task_manager::instance();

    std::shared_ptr<task_group_base> _hw_group = std::make_shared<hellow_world_task_group>(5);

    ins->add_group(_hw_group);
    TASK_MSG msg;
    msg.type = MSG_TYPE::HW;
    msg.body = nullptr;

    
    ins->post(GROUP_TYPE::HELLOWORLD, msg);
}
