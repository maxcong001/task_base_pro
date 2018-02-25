#include "task_base_pro/task_worker.hpp"

void evfdCallback(int fd, short event, void *args)
{
    uint64_t one;
    int ret = read(fd, &one, sizeof one);
    if (ret != sizeof one)
    {
        __LOG(warn, "read return : " << ret);
        return;
    }
    //__LOG(debug, "task with id : " << fd << " receive eventfd message, count is : " << one);
    // for (uint64_t i = 0; i < one; i++)
    // {
    task_base *tmp = reinterpret_cast<task_base *>(args);
    tmp->process_msg(one);
    // }
}
