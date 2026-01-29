/*
 * f3.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/* ged */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"
#include "forest.h"
#include <stdproperties.h>

object hacke;

void reset_room();

void
create_room()
{
    set_short("Forest");
    set_long("You are standing on a small path leading through the " +
             "woods. The trees surrounding you are dark and ugly, " +
             "except for one of them that looks a little peculiar.\n");

    GRASS;
    TREES;

    add_item("tree", "The tree has an orange birdhouse nailed to its " +
             "side.\n");
    add_item("birdhouse", "This is the home of some sort of bird. It is " +
             "painted a brilliant orange colour for some reason.\n");

    add_exit("f4", "east");
    add_exit("f1", "southwest");

    add_prop(OBJ_S_WIZINFO,
             "This is intended to be a checkpoint in the quest given " +
             "by the Mayor.\n");

    reset_room();
}

void
reset_room()
{
    if (hacke)
        return;

    tell_room(TO, "A woodpecker comes flying.\n");
    hacke = clone_object(ROKEDIR + "npc/woodpecker");
    hacke->move(TO);
}
