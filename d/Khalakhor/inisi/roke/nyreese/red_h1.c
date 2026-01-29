/*
 * red_h1.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

object goblin;

void reset_room();

void
create_room()
{
    set_short("a smelly building");
    set_long("This is a disgusting old building. Rats run across the " +
             "floor and there are spiders everywhere. The smell of " +
             "goblins is extremly strong here. You feel a little " +
             "sick.\n");

    add_item("rats",
             "The rats are too quick, they run away when you look at them.\n");
    add_item("spiders", "They are black, very small and have yellow legs.\n");

    add_exit("red_r5", "east");
    reset_room();
}

void
reset_room()
{
    if (goblin)
        return;

    goblin = clone_object(ROKEDIR + "npc/goblin1");
    goblin->equip_me();
    goblin->move(TO);
}
