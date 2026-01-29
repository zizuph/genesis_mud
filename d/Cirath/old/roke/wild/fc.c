/*
 * fc.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/* ged */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"
#include <stdproperties.h>

object guard;

void reset_room();

void
create_room()
{
    set_short("Forest");
    set_long("You are walking around in the middle of the dark forest. The " +
             "trees around you are very large, and you can hardly see any " +
             "light here. Someone has built a barricade to prevent you from " +
             "going south. You can also hear different sounds but you can't " +
             "specify which direction they come from.\n");

    add_item("barricade",
             "Its very well built. Only a professional squad could " +
             "do this.\n");

    add_exit("fa", "north");
    add_exit("fd", "south", "@@block");
    add_exit("fm", "east");

    reset_room();
}

int
block()
{
    if (MAL("guard") && !TP->query_prop(OBJ_I_INVIS))
    {
        write("The guard stops you from entering the camp.\n");
        return 1;
    }
    return 0;
}

void
reset_room()
{
    if (guard)
        return;

    guard = clone_object(ROKEDIR + "npc/campguard");
    guard->equip_me();
    guard->move(TO);
}
