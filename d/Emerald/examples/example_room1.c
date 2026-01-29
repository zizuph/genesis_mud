/*
 * This example demonstrates how to make a room which has a long
 * description that changes according to the player's last room.
 */

inherit "/d/Emerald/std/room";

#include <stdproperties.h>

void
create_emerald_room()
{
    set_em_long("@@special_long@@This is a very pretty room.\n");
}

string
special_long()
{
    object last_room = this_player()->query_prop(LIVE_O_LAST_ROOM);
    string filename;

    if (!last_room)
    {
        return "You came from nowhere!  ";
    }

    filename = file_name(last_room);

    if (filename == "/d/Emerald/some/other/room")
    {
        return "You came from some other room.  ";
    }

    if (filename == "/d/Emerald/a/totally/different/room")
    {
        return "You came from a totally different room.  ";
    }

    return "You came from some room I don't know about!  ";
}
