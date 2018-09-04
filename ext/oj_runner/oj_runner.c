#include "oj_runner.h"
#include "convert.h"
#include "extconf.h"
#include "run.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int init_run(struct Runobj *runobj, VALUE args)
{
    VALUE cmd_obj, fd_obj, time_obj, memory_obj, uid_obj, trace_obj, calls_obj;
    int i;
    Check_Type(args, T_HASH);

    if ((cmd_obj = rb_hash_aref(args, rb_str_new2("cmd"))) == Qnil)
        rb_raise(rb_eRuntimeError, "key 'cmd' required");
    else
    {
        Check_Type(cmd_obj, T_ARRAY);
        runobj->cmd = array2cmd(cmd_obj);
    }

    if ((fd_obj = rb_hash_aref(args, rb_str_new2("fd_in"))) == Qnil)
        runobj->fd_in = -1;
    else
        runobj->fd_in = FIX2INT(fd_obj);
    if ((fd_obj = rb_hash_aref(args, rb_str_new2("fd_out"))) == Qnil)
        runobj->fd_out = -1;
    else
        runobj->fd_out = FIX2INT(fd_obj);
    if ((fd_obj = rb_hash_aref(args, rb_str_new2("fd_err"))) == Qnil)
        runobj->fd_err = -1;
    else
        runobj->fd_err = FIX2INT(fd_obj);

    if ((time_obj = rb_hash_aref(args, rb_str_new2("timelimit"))) == Qnil)
        rb_raise(rb_eRuntimeError, "key 'timelimit' required");
    else
        runobj->time_limit = FIX2INT(time_obj);

    if ((memory_obj = rb_hash_aref(args, rb_str_new2("memorylimit"))) == Qnil)
        rb_raise(rb_eRuntimeError, "key 'memorylimit' required");
    else
        runobj->memory_limit = FIX2INT(memory_obj);

    if ((uid_obj = rb_hash_aref(args, rb_str_new2("uid"))) == Qnil)
        runobj->uid = -1;
    else
        runobj->uid = FIX2INT(uid_obj);

    if ((trace_obj = rb_hash_aref(args, rb_str_new2("trace"))) != Qnil)
    {
        if (trace_obj == Qtrue)
        {
            runobj->trace = 1;

            if ((calls_obj = rb_hash_aref(args, rb_str_new2("calls"))) == Qnil)
                rb_raise(rb_eRuntimeError, "key 'calls' required in trace mode");
            Check_Type(calls_obj, T_ARRAY);
            if (!array2calls(calls_obj, runobj->call_table))
                return 0;

            if ((runobj->files = rb_hash_aref(args, rb_str_new2("files"))) == Qnil)
                rb_raise(rb_eRuntimeError, "key 'files' required in trace mode");
            Check_Type(runobj->files, T_HASH);
        }
        else
            runobj->trace = 0;
    }
    else
        runobj->trace = 0;

    return 1;
}

VALUE run(VALUE self, VALUE args)
{
    struct Runobj runobj = {0};
    struct Result result = {0};
    if (!init_run(&runobj, args))
        return Qnil;

    if (!run_it(&runobj, &result))
        return Qnil;

    if (runobj.cmd)
        free((void *)runobj.cmd);
    return Qtrue;
}

void Init_oj_runner()
{
    // VALUE cOjRunner = rb_const_get(rb_cObject, rb_intern("OjRunner"));
    VALUE cOjRunner = rb_define_class("OjRunner", rb_cObject);

    rb_define_singleton_method(cOjRunner, "run", run, 1);
}
