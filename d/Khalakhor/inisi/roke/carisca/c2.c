/*
 * c2.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";
#include "defs.h"

object grugg;

void reset_room();

void
create_room()
{
    set_short("grugg cave");
    set_long("This is a small cave, filled with bones and leftovers. A " +
             "small crack leads downwards, and from the smell of sulphur " +
             "you realize that the crack leads all the way down to the " +
             "boiling inside of the planet.\n");

    add_item("crack", "The crack smells of sulphur.\n");
    add_item("bones", "The bones have been chewed on.\n");

    add_exit("f1", "northwest");

    reset_room();
}

void
reset_room()
{
    if (objectp(grugg))
        return;

    grugg = clone_object(ROKEDIR + "npc/grugg");
    grugg->move(TO);

    tell_room(TO, "A nasty grugg comes from the crack in the ground.\n");
}
