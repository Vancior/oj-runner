#include "limit.h"
#include <sys/resource.h>
#include <sys/time.h>

#define RAISE_EXIT(err) {\
    last_limit_err = err;\
    return 0;\
}

const char *last_limit_err;

int set_limit(struct Runobj *runobj)
{
    /* note! most of the limits won't work in WSL */
    struct rlimit rl;

    rl.rlim_cur = runobj->time_limit / 1000 + 1;
    if (runobj->time_limit % 1000 > 800)
        rl.rlim_cur += 1;
    rl.rlim_max = rl.rlim_cur + 1;
    if (setrlimit(RLIMIT_CPU, &rl))
        RAISE_EXIT("set RLIMIT_CPU failed");

    rl.rlim_cur = runobj->memory_limit * 1024;
    rl.rlim_max = rl.rlim_cur + 1024;
    if (setrlimit(RLIMIT_DATA, &rl))
        RAISE_EXIT("set RLIMIT_DATA failed");

    rl.rlim_cur = runobj->memory_limit * 1024 * 2;
    rl.rlim_max = rl.rlim_cur + 1024;
    if (setrlimit(RLIMIT_AS, &rl))
        RAISE_EXIT("set RLIMIT_AS failed");

    /* note! RLIMIT_STACK is not supported in WSL(1803) */
    rl.rlim_cur = 256 * 1024 * 1024;
    rl.rlim_max = rl.rlim_cur + 1024;
    if (setrlimit(RLIMIT_STACK, &rl))
        RAISE_EXIT("set RLIMIT_STACK failed");

    return 1;
}
