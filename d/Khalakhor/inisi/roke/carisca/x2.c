/*
 * x2.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit CARISCADIR + "earthroom";

#include <macros.h>

object ghul;

void reset_room();

void
create_earthroom()
{
    set_short("Inside a small hole in the ground");
    set_long("You are inside a small hole in the ground. The walls " +
             "around you are all dirt, and some tree-roots are clearly " +
             "visible in the ceiling. It smells rather strange here.\n");

    add_item("root", "They emerge from the ceiling.\n");
    add_item("walls", "As you are underground, you are surrounded by dirt.\n");

    add_wall("x3", "east");
    add_wall("x1", "north", "@@block");

    reset_room();
}

void
reset_room()
{
    if (ghul)
        return;

    ghul = clone_object(ROKEDIR + "npc/ghoul");
    ghul->equip_me();
    ghul->move(TO);
}

int
block()
{
    if (!MAL("ghoul"))
        return 0;

    write("You try to move north, but the ghoul stops you.\n");
    say(QCTNAME(TP) + " tries to walk north but is stopped by the ghoul.\n");

    return 1;
}
