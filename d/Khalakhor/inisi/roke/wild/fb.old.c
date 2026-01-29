/*
 * fb.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 * Allowed sneaking by guard - Tapakah, July 2011.
 */

/* ged */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit "/std/room";
inherit ROKEDIR + "lib/roomcode";

#include "forest.h"
#include <stdproperties.h>
#include <macros.h>
object guard;

void reset_room();

void
create_room()
{
    init_sp_quest();

    set_short("Forest");
    set_long("You are standing in a small clearing in the forest. In the " +
             "middle of it is a tiny pond, formed by a stream that runs " +
             "from the east. Someone has built a large barricade here. " +
             "The barricade is built to protect something southeast from here." +
             "\n");

    add_item("barricade",
             "It's very well built. Only a professional squad could " +
             "do this.\n");

    TREES;
    TREE2;
    GRASS;

    BEACH;

    add_cmd_item("water", "drink", "Ah, feels good.\n");

    add_exit("f7", "west");
    add_exit("fd", "southeast", "@@block");

    reset_room();
}

int
block()
{
  if (guard && present(guard) && CAN_SEE(guard, TP))
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

void
init()
{
    ::init();

    initrc();
}
