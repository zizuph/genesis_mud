/*
 * ihut.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/* Ogions hut north of Re-Albi  */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

object ogion;

void reset_room();

void
create_room()
{
    set_short("Inside a hut");
    set_long("You are inside an old hut. There are very few things here " +
             "and whoever lives here must prefer a simple life.\n");

    add_exit("ohut", "out");

    INSIDE;
    reset_room();
}

void
reset_room()
{
    if (!ogion)
    {
        ogion = clone_object(ROKEDIR + "npc/ogion");
        ogion->equip_me();
        ogion->move(TO);
        tell_room(TO, "A silent human arrives.\n");
    }
}
