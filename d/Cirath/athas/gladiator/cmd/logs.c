#include "defs.h"

/*
 * This function handles viewing of the various logs.
 * For now, all Overseers have access to the logs.
 */
public int
_cmd_logs(string str)
{
    int mored;
    string *arr;

    if (!strlen(str))
    {
        return notify_fail("Available logs are:\n  "+
          "join, quit, lesser, punish, brutus\n");
    }

    arr = explode(str, " ");
    if ((sizeof(arr) == 2) && (arr[1] == "more"))
        mored = 1;

    switch(arr[0])
    {
    case "join":
        str = LOG_JOIN;
        break;

    case "quit":
        str = LOG_QUIT;
        break;

    case "lesser":
        str = LOG_LESSER;
        break;

    case "punish":
        str = LOG_PUNISH;
        break;

    case "brutus":
        str = LOG_BRUTUS;
        break;

    default:
        write("That does not appear to be a valid logfile.\n");
        return 1; break;
    }

    if (file_size(str) == -1)
    {
        write("That logfile appears to not contain any data at "+
          "the present time.\n");
        return 1;
    }

    if (mored)
        this_player()->more(read_file(str));
    else
        tail(str);

    return 1;
}
