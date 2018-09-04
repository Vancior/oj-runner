#include "run.h"
#include "limit.h"
#include <fcntl.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

// #define _GNU_SOURCE

#define RAISE_EXIT(err) {\
    int r = write(fd_err[1], err, strlen(err));\
    _exit(r);\
}

/*
int run_it(struct Runobj *runobj, struct Result *result)
{
    pid_t pid;
    int fd_err[2];

    if (pipe2(fd_err, O_NONBLOCK))
    rb_raise(rb_eRuntimeError, "pipe2 failed");

    pid = vfork();
    if (pid < 0)
    {
        close(fd_err[0]);
        close(fd_err[1]);
        rb_raise(rb_eRuntimeError, "vfork failed");
    }

    if (pid == 0)
    {
        close(fd_err[0]);

        if (runobj->fd_in != -1)
            if (dup2(runobj->fd_in, 0) == -1)
                RAISE_EXIT("dup2 stdin failed");

        if (runobj->fd_out != -1)
            if (dup2(runobj->fd_out, 1) == -1)
                RAISE_EXIT("dup2 stdout failed");

        if (runobj->fd_err != -1)
            if (dup2(runobj->fd_err, 2) == -1)
                RAISE_EXIT("dup2 stderr failed");

        if (!set_limit(runobj))
            RAISE_EXIT(last_limit_err);

        if (runobj->uid != -1)
            if (setuid(runobj->uid))
                RAISE_EXIT("setuid failed");

        if (runobj->trace)
            if (ptrace(PTRACE_TRACEME, 0, NULL, NULL) == -1)
                RAISE_EXIT("TRACEME failed");

        if (execvp(runobj->cmd[0], runobj->cmd) == -1)
            RAISE_EXIT("execvp failed");
    }
    else
    {
        int r;
        char buffer[100] = {0};
        close(fd_err[1]);
        r = read(fd_err[0], buffer, 90);
        if (r > 0) {
            waitpid(pid, NULL, WNOHANG);
            rb_raise(rb_eRuntimeError, "%s", buffer);
            return 0;
        }
        close(fd_err[0]);
        // rb_raise(rb_eRuntimeError, "parent raising");
        return 1;
    }
}
*/
int run_it(struct Runobj *runobj, struct Result *result)
{
    pid_t pid;
    pid = vfork();
    if (pid < 0)
        rb_raise(rb_eRuntimeError, "fail");
    else if (pid == 0)
        return 1;
    else
    {
        printf("child: %d\n", pid);
        return 1;
    }
}
