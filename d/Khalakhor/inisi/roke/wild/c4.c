/*
 * c4.c
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
    set_short("bottom of the hole");
    set_long("This is the bottom of the hole. Above you, the rope disappears " +
             "in darkness, and when you look around you, you see a small rift " +
             "in the eastern wall, going deep into the mountain.\n");

    add_item("rope", "@@rope");
    add_item("rift", "It looks like you could enter it.\n");

    add_exit("c3", "up");
    add_exit("t1", "east");

    DARK;
    INSIDE;
}

string
rope()
{
    return present("rope", find_object(WILDDIR + "c2"))->long();
}
