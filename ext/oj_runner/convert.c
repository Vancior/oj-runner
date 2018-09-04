#include "convert.h"
#include <string.h>
#include <stdio.h>

char *const * array2cmd(VALUE array)
{
    VALUE one_cmd;
    char *cmd_temp;
    const char **buffer;
    long cmd_total_len = 0;
    int cmd_len = RARRAY_LEN(array), i;

    if (cmd_len == 0)
        rb_raise(rb_eRuntimeError, "cmd empty");

    buffer = (const char **) malloc(sizeof(char *) * (cmd_len + 1));

    for (i = 0; i < cmd_len; ++i)
    {
        one_cmd = rb_ary_entry(array, i);
        SafeStringValue(one_cmd);
        buffer[i] = StringValueCStr(one_cmd);
        // if (strlen(cmd_temp) + cmd_total_len + 1 >= 255)
        //     rb_raise(rb_eRuntimeError, "cmd too long");
        // cmd_total_len += strlen(cmd_temp) + 1;
        // strcat(buffer, cmd_temp);
        // strcat(buffer, " ");
        // ++cmd_len;
    }

    /* important! the second arg of execvp end with NULL */
    buffer[cmd_len] = NULL;

    return (char *const *) buffer;
}

int array2calls(VALUE array, u_char call_table[])
{
    VALUE one_call;
    int call_index;
    long call_count = 0;

    memset(call_table, 0, sizeof(u_char) * CALLS_MAX);

    while ((one_call = rb_ary_entry(array, call_count)) != Qnil)
    {
        Check_Type(one_call, T_FIXNUM);
        call_index = FIX2INT(one_call);
        call_table[call_index] = 1;
    }

    return 0;
}
