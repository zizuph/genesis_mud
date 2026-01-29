/*
 * i2.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "../../defs.h"

object hydra;

int
query_hydra()
{
    return (objectp(hydra) && present(hydra));
}

void
reset_room()
{
    if (objectp(hydra))
        return;

    hydra = clone_object(SHIPDIR + "monster/hydra");
    hydra->move_living("M", TO);
    tell_room(this_object(), "A hydra arrives.\n");
}

void
create_room()
{
    set_short("The middle of the island");

    set_long("You are at in the middle of the small island. " +
             "There is no vegetation here and the look of this place is " +
             "very dull and boring. To the west you can see the beach where " +
             "you came from and to the east the only thing you can see is " +
             "the vast sea.\n");

    add_exit("i1", "west");

    reset_room();
}
