#include <ruby.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "extconf.h"
#include "oj_runner.h"
#include "oj_runner.h"

int init_run(struct Runobj *runobj, VALUE args)
{
    VALUE cmd_array, fd_obj, time_obj, memory_obj, uid_obj, trace_obj, calls_obj;
    Check_Type(args, T_HASH);

    if ((cmd_array = rb_hash_aref(args, rb_str_new2("cmd"))) == Qnil)
        rb_raise(rb_eRuntimeError, "key 'cmd' required");
    else
    {
        Check_Type(cmd_array, T_ARRAY);
        if (!array2cmd(cmd_array, runobj->cmd))
            return 0;
        printf("%s\n", runobj->cmd);
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
    
    return 1;
}

VALUE run(VALUE self, VALUE args)
{
    struct Runobj runobj = {0};
    struct Result result = {0};
    init_run(&runobj, args);
    return Qtrue;
}

void Init_oj_runner()
{
    // VALUE cOjRunner = rb_const_get(rb_cObject, rb_intern("OjRunner"));
    VALUE cOjRunner = rb_define_class("OjRunner", rb_cObject);

    rb_define_singleton_method(cOjRunner, "run", run, 1);
}