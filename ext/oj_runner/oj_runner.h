
enum JUDGE_RESULT
{
    AC = 0,
    PE,
    TLE,
    MLE,
    WA,
    RE,
    OLE,
    CE,
    SE
};

struct Result
{
    int judge_result;
    int time_used, memory_used;
    int re_signum;
    int re_call;
    const char *re_file;
    int re_file_flag;
};

struct Runobj
{
    char *const *args;

    int fd_in, fd_out, fd_err;
    int time_limit, memory_limit;
    int runner;
    int trace;
};