#include "defs.h"

inherit MIST_ISLE_BASE;

static string *left_shore_exits = ({}), *right_shore_exits = ({});

public string *
query_exit_descs()
{
    string *dirs = ::query_exit_descs();

    if (sizeof(left_shore_exits))
    {
        dirs += ({ "left along the shore" });
    }

    if (sizeof(right_shore_exits))
    {
        dirs += ({ "right along the shore" });
    }

    return dirs;
}

public void
create_mist_shore_room()
{
}

nomask void
create_mist_isle_room()
{
    create_mist_shore_room();
}

public void
add_mist_exit(int dirs, string path, string cmd)
{
    ::add_mist_exit(dirs, path, cmd);

    if (dirs & LSHORE_EXIT)
    {
        left_shore_exits += ({ path });
    }
    else if (dirs & RSHORE_EXIT)
    {
        right_shore_exits += ({ path });
    }
}

public void
walk_left_shore()
{
    int i = sizeof(left_shore_exits);
    if (i)
    {
        walk_mist(left_shore_exits[random(i)]);
    }
    else
    {
        write("You can't find a path in that direction.\n");
    }
}

public void
walk_right_shore()
{
    int i = sizeof(right_shore_exits);
    if (i)
    {
        walk_mist(right_shore_exits[random(i)]);
    }
    else
    {
        write("You can't find a path in that direction.\n");
    }
}

public int
walk(string str)
{
    string *preps = ({ "right", "left" });
    if (!strlen(str) ||
        !parse_command(str, ({}),
        "[to] [the] %p [along] / [following] [the] 'shore' / 'water' / 'surf'",
        preps))
    {
        return ::walk(str);
    }

    if (preps[0] == "left")
    {
        walk_left_shore();
    }
    else
    {
        walk_right_shore();
    }

    return 1;
}
