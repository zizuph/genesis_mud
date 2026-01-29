/*
 * c3.c
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
    set_short("down the hole");
    set_long("You are climbing on a rope somewhere in a deep hole.\n");

    DARK;
    INSIDE;

    add_item("rope", "@@rope");

    add_exit("c2", "up");
    add_exit("c4", "down");
}

string
rope()
{
    return present("rope", find_object(WILDDIR + "c2"))->long();
}
