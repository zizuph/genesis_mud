/*
 * ff.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/* ged */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"
#include "forest.h"
#include <stdproperties.h>
#include <macros.h>

object guard;

void reset_room();

void
create_room()
{
    set_short("Forest");
    set_long("You are standing in the middle of a big forest. You feel " +
             "a little lost, as you look at the big trees around you. " +
             "To the east you can see some tents and a flickering light. " +
             "Someone has built a barricade to prevent you from going east.\n");

    add_item("barricade",
             "Its very well built. Only a professional squad could" +
             " do this.\n");

    TREES;
    TREE1;

    add_exit("fd", "east", "@@block");
    add_exit("fe", "southwest");

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
