#include "convert.h"

int array2cmd(VALUE array, char *buffer)
{
    VALUE one_cmd;
    char *cmd_temp;
    long cmd_len = 0, i = 0, cmd_total_len = 0;
    while (rb_ary_entry(array, cmd_len) != Qnil)
        ++cmd_len;
    if (cmd_len == 0)
        return 0;
    for (i = 0; i < cmd_len; ++i)
    {
        one_cmd = rb_ary_entry(array, i);
        SafeStringValue(one_cmd);
        cmd_temp = StringValueCStr(one_cmd);
        if (strlen(cmd_temp) + cmd_total_len + 1 >= 255)
            rb_raise(rb_eRuntimeError, "cmd too long");
        cmd_total_len += strlen(cmd_temp) + 1;
        strcat(buffer, cmd_temp);
        strcat(buffer, " ");
    }
    return 1;
}