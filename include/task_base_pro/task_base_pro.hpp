#include "logger/logger.hpp"
#include "translib/loop.h"
#include "translib/eventClient.h"
#include "translib/eventServer.h"
#include "translib/timerManager.h"
#include "translib/timer.h"
#include "task_base_pro/task_group.hpp"
#include "task_base_pro/task_worker.hpp"
#include "util.hpp"

#include <memory>
#include <string>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <array>
#include <cstdio>
#include <cinttypes>
#include <initializer_list>

#define MAX_GROUP_SIZE 10
#define MAX_WORKER_SIZE 10

using group_ptr_t = std::shared_ptr<task_group>;
using worker_ptr_t = std::shared_ptr<task_worker>;
using group_array = std::array<group_ptr_t, MAX_GROUP_SIZE>;
using worker_array = std::array<worker_ptr_t, MAX_WORKER_SIZE>;

class task_base_pro
{
  public:
    task_base_pro()
    {
        _group_array.fill(nullptr);
    }

    bool init()
    {
    }
    // after init, if any group change, must refresh!!!!
    bool refresh()
    {
    }

    bool add_group(group_ptr_t _group)
    {
    }

    group_array _group_array;
    //std::uint32_t _group_number;
};