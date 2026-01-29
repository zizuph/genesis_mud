/*
 * cas_b5.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/*  Ged  */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

object und;

void
reset_room()
{
    if (und)
        return;

    und = clone_object(ROKEDIR + "npc/undertaker");
    und->equip_me();
    und->move_living("xxx", TO);
}

void
create_room()
{
    set_short("Castle in Cadu");
    set_long("This is a cold, narrow corridor.\n" +
             "A thin share of light cuts through the corridor " +
             "coming from a window high up the west wall.\n");

    add_item("window", "It is too high up.\n");

    add_exit("cas_b1", "north");
    add_exit("cas_b6", "east");
    add_exit("cas_b9", "south");
    INSIDE;

    reset_room();
}
