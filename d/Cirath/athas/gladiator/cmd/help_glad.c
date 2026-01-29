#include "defs.h"

public int
_cmd_help_glad(string str)
{
    string *args = explode((str ? str : ""), " ");
    int sz = sizeof(args);

    if(sz == 0 || (args[0] != "gladiator" && args[0] != "glad"))
    {
        return 0;
    }

    object tp = this_player();

    setuid();
    seteuid(getuid());

    if(sz == 1)
    {
        string *files = filter(get_dir(GLAD_HELP), &operator(==)(".gh") @ &extract(, -3));

        if(!sizeof(files))
        {
            return notify_fail("There doesn't appear to be any help!\n");
        }

        files = map(map(files, &extract(, 0, -4)), capitalize);

        write("Help is available to Gladiators on these subjects:\n");
        write(sprintf("\n%-#78s\n", implode(files, "\n")));

        if(POSITION(tp) != POS_NONE)
        {
            files = filter(get_dir(GLAD_HELP), &operator(==)(".oh") @ &extract(, -3));

            if(sizeof(files))
            {
                files = map(map(files, &extract(, 0, -4)), capitalize);
                write("\nHelp is available to Overseers on these subjects:\n");
                write(sprintf("\n%-#78s\n", implode(files, "\n")));
            }
        }

        write("\nUse 'help glad[iator] <subject>' to access help files.\n\n");
        return 1;
    }

    string file;

    if((file = sprintf("%s%s.gh", GLAD_HELP, args[1])) && file_size(file) > 0)
    {
        tp->more(read_file(file));
        return 1;
    } else if(POSITION(tp) != POS_NONE) {
        if((file = sprintf("%s%s.oh", GLAD_HELP, args[1])) && file_size(file) > 0)
        {
            tp->more(read_file(file));
            return 1;
        }
    }

    return 0;
}
