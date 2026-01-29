/*
 * x1.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit CARISCADIR + "earthroom";

#include <macros.h>

object ghu;

void reset_room();

void
create_earthroom()
{
    set_short("Inside a small hole in the ground");
    set_long("You are inside a small hole in the ground. The walls " +
             "around you are all dirt, and some tree-roots are clearly " +
             "visible in the ceiling. It smells rather strange here.\n");

    add_wall("x2", "south");

    add_item("root", "They emerge from the ceiling.\n");

    reset_room();
}

void
reset_room()
{
    if (!present("skeleton", TO))
        clone_object(ROKEDIR + "obj/spellp")->move(TO);

    if (ghu)
        return;

    ghu = clone_object(ROKEDIR + "npc/ghoul");
    ghu->equip_me();
    ghu->move(TO);
}
