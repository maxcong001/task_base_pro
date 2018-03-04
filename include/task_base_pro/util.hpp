

#if __cplusplus >= 201703L
// use std::any
#include <any>
#define TASK_ANY std::any
#define TASK_ANY_CAST std::any_cast
#else
#include <boost/any.hpp>
#define TASK_ANY boost::any
#define TASK_ANY_CAST boost::any_cast
#endif
// heartbeat interval between  hb task to all the tasks
#define HB_INTERVAL 5

#define MAX_WORKER_SIZE 10

enum class GROUP_TYPE : unsigned int //std::uint32_t
{
    WORKER = 0,
    MANAGER,
    GROUP_MAX,
};
using MAX_GROUP_SIZE = GROUP_TYPE::GROUP_MAX;
// message tyep
enum class MSG_TYPE : unsigned int
{
    // for manager
    MANAGER_HB_REQ = 0,
    // for worker
    MANAGER_HB_RSP

};

struct TASK_MSG
{
    msg_type type;
    TASK_ANY body;
};

struct TASK_HB_REQ_MSG
{
    GROUP_TYPE from_group;
    std::uint32_t from_index;
};
struct TASK_HB_RSP_MSG
{
    GROUP_TYPE from_group;
    std::uint32_t from_index;
};

typedef std::queue<TASK_MSG> TASK_QUEUE;