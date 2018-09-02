#include <ruby.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "extconf.h"
#include "oj_runner.h"

static VALUE run(VALUE self, VALUE args)
{
    struct Runobj runobj = {0};
    struct Result result = {0};
    VALUE cmd, one_cmd;
    char cmd_combined[255] = "", *cmd_temp;
    long cmd_len = 0, i = 0, cmd_total_len = 0;
    Check_Type(args, T_HASH);
    cmd = rb_hash_aref(args, rb_str_new2("cmd"));
    if (cmd == Qnil)
        rb_raise(rb_eRuntimeError, "key 'cmd' has to be set");
    else
    {
        Check_Type(cmd, T_ARRAY);
        while (rb_ary_entry(cmd, cmd_len) != Qnil)
            ++cmd_len;
        // cmd_cptr = malloc(sizeof(char *) * cmd_len);
        for (i = 0; i < cmd_len; ++i)
        {
            one_cmd = rb_ary_entry(cmd, i);
            SafeStringValue(one_cmd);
            cmd_temp = StringValueCStr(one_cmd);
            if (strlen(cmd_temp) + cmd_total_len + 1 >= 255)
                rb_raise(rb_eRuntimeError, "cmd too long");
            cmd_total_len += strlen(cmd_temp) + 1;
            strcat(cmd_combined, cmd_temp);
            strcat(cmd_combined, " ");
        }
        return rb_str_new2(cmd_combined);
    }
    return Qtrue;
}

void Init_oj_runner()
{
    // VALUE cOjRunner = rb_const_get(rb_cObject, rb_intern("OjRunner"));
    VALUE cOjRunner = rb_define_class("OjRunner", rb_cObject);

    rb_define_singleton_method(cOjRunner, "run", run, 1);
}