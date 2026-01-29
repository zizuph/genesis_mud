inherit "/std/room";

#include <composite.h>

void
create_cave_room()
{
}

string
exits()
{
    if (this_player()->query_wiz_level())
    {
        return " (" + COMPOSITE_WORDS(query_exit_cmds()) + ")";
    }

    return "";
}

nomask void
create_room()
{
    create_cave_room();

    set_short(query_short() + "@@exits@@");
}

