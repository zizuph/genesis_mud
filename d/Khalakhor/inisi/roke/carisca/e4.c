/*
 * e4.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

void
create_room()
{
    set_short("edge of the volcano");
    set_long("You are standing south of a boiling lake of lava. " +
             "To the north of you a small path leads down into " +
             "the crater, towards a high stone pillar in the middle " +
             "of the lava. Occasionally you see a grugg swimming " +
             "around in the crater.\n");

    add_exit("l2", "north", "@@block");
    add_exit("e5", "east");
}

int
block()
{
    if (!(TP->query_prop(COLDFEET)))
    {
        TP->catch_msg("The lava is too hot!\n");
        return 1;
    }
    TP->add_prop(COLDFEET, 1);
    return 0;
}
