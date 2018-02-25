

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
enum class group_type : unsigned int //std::uint32_t
{
    worker = 0,
    manager,
    heart_beat,

};
// message tyep
enum class msg_type : unsigned int
{
    // for manager
    manager_hb_req = 0,
    // for worker
    manager_hb_resp

};

struct TASK_MSG
{
    msg_type type;
    TASK_ANY body;
}
typedef std::queue<TASK_MSG> TASK_QUEUE;