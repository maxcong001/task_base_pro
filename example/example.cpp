
#include "logger/logger.hpp"
#include "events/include"
#include "task_base_pro/include"
int main()
{
    set_log_level(logger_iface::log_level::debug);
    set_max_log_buff(10);

    dump_log();
    Global::initialize();
    auto ins = task_manager::instance();

    std::shared_ptr<task_group_base> _hw_group = std::make_shared<hellow_world_task_group>(5);
    _hw_group->init();

    ins->add_group(_hw_group);
    TASK_MSG msg;
    msg.type = MSG_TYPE::HW;
    msg.body = nullptr;
    for (int i = 0; i < 1000; i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        ins->post(GROUP_TYPE::HELLOWORLD, msg);
    }
    std::this_thread::sleep_for(std::chrono::seconds(11));
}
