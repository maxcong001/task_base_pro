#pragma once
#if 0
#include "logger/logger.hpp"

#include "task_base_pro/task_group.hpp"
#include "task_base_pro/task_worker_thread.hpp"
#include "task_base_pro/util.hpp"

#include <memory>
#include <string>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <array>
#include <cstdio>
#include <cinttypes>
#include <initializer_list>

using group_ptr_t = std::shared_ptr<task_group_base>;
using worker_ptr_t = std::shared_ptr<task_worker_thread>;
using group_array = std::array<group_ptr_t, GROUP_TYPE::GROUP_MAX>;
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
};
#endif