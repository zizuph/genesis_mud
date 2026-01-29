/*
 * cas_a9.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/*  Ged  */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

object spirit;

void reset_room();

void
create_room()
{
    set_short("Southwest corner of the Castle");
    set_long("This is the most uninteresting room of the castle. " +
             "The walls are built of raw, unpolished granite, and " +
             "the only thing preventing it from being completely dark " +
             "is a weak light coming from the open door to the southwest.\n");

    add_exit("cas_a5",  "north");
    add_exit("cas_a10", "east");
    add_exit("cas_t13", "southwest");

    reset_room();
}

void
reset_room()
{
    if (spirit)
        return;

    spirit = clone_object(ROKEDIR + "npc/spirit");
    spirit->move(TO);

    tell_room(TO, "A transparent spirit arrives.\n");
}
