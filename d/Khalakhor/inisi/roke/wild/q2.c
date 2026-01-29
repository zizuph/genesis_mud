/*
 * q2.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>

void
create_room()
{
    set_short("on a very, very narrow path");
    set_long(VBFC_ME("descr"));

    add_exit("q3", "north", -2, 10);
    add_exit("q1", "west", -1, 0);
}

string
descr()
{
    string move = this_player()->query_prop(LIVE_S_LAST_MOVE);
    if (move == "south" || move == "west")
    {
        return "You are on a narrow path going down from a mountain " +
            "top. It is getting rather steep now, and you feel " +
            "a little tired due to the thin air. Far below you " +
            "is the old monastery, residing on a small plateau.\n";
    }
    else
    {
        return "You are on a narrow path leading towards a mountain " +
            "top. It is getting rather steep now, and you feel " +
            "a little tired due to the thin air. Far below you " +
            "is the old monastery, residing on a small plateau.\n";
    }

}
