/*
 * p4.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"
#include <ss_types.h>

void
create_room()
{
    set_short("at a steep cliff");
    set_long("You are just below a steep cliff that rises high above you. " +
             "There is something strange about this place, perhaps that " +
             "the well-travelled path ends here and there seems to be no " +
             "other exit than to go back where you came from.\n");

    add_item("cliff",
             "Someone has carved small footsteps in the cliff, making " +
             "it possible to climb up.\n");

    add_exit("p3", "west");

    add_cmd_item(({"up", "cliff"}), "climb", "@@climb");
}

int
climb()
{
    if (TP->query_skill(SS_CLIMB) > 9)
    {
        TP->move_living("climbing up the cliff", WILDDIR + "p5");
        return 1;
    }
    if (TP->query_skill(SS_CLIMB) > 4)
    {
        write("You almost manage to climb up, but it is a little too hard for you.\n");
        return 1;
    }
    write("You are not skilled enough to climb up.\n");
    return 1;
}
