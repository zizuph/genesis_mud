/*
 * x6.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit CARISCADIR + "earthroom";

void
create_earthroom()
{
    set_short("Inside a small hole in the ground");
    set_long("You are inside a small hole in the ground. The walls " +
             "around you are all dirt, and some tree-roots are clearly " +
             "visible in the ceiling. It smells rather strange here.\n");

    add_item("root", "They emerge from the ceiling.\n");

    add_wall("x5", "west");
    add_wall("f7", "up");
}
