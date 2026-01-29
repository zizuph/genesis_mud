/*
 * x4.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit CARISCADIR + "earthroom";

object ghu;

void reset_room();

void
create_earthroom()
{
    set_short("inside a small hole in the ground\n");
    set_long("You are inside a small hole in the ground. The walls " +
             "around you are all dirt, and some tree-roots are clearly " +
             "visible in the ceiling. It smells rather strange here.\n");

    add_item("root", "They emerge from the ceiling.\n");

    add_wall("x5", "east");

    reset_room();
}

void
reset_room()
{
    if (ghu)
        return;

    ghu = clone_object(ROKEDIR + "npc/ghoul");
    ghu->equip_me();
    ghu->move(TO);
}
