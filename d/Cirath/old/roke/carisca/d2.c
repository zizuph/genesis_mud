/*
 * d2.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

void
create_room()
{

    set_short("The entrance of the caves");
    set_long("You are standing in the entrance of a complex cave system, " +
             "built by dwarves many years ago. To the north of you is, " +
             "strangely enough, a beach. Obviously the caves are " +
             "inhabitated by very " +
             "brave dwarves, that have overcome their fear of water.\n");

    add_exit("d1", "west");
    add_exit("d3", "east");
    add_exit("d4", "south");
    add_exit("waterhandler", "north", "@@block");

    BEACH;
}

int
block()
{
    if (TP->query_npc())
    {
        write("You are afraid of water, small NPC!\n");
        return 1;
    }

    (CARISCADIR + "waterhandler")->trans("north", 3, 3);
    return 1;
}
