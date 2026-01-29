/*
 * dc1.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

void
reset_room()
{
    object obj;

    if (!present("pearl", TO))
        clone_object(ROKEDIR + "obj/sak")->move(TO);

    while (obj = present("rubble", TO))
        obj->remove_object();
}

void
create_room()
{
    set_short("huge cave");
    set_long("The smell of sulphur is rather strong here. The walls are " +
             "scratched as from giant claws, and on the floor are small " +
             "fragments of bones. In the west wall is a small hole.\n");

    add_item("walls", "The walls are scratched from giant claws.\n");
    add_item("bones", "They look like human bones.\n");
    add_item("hole", "Unfortunately it is too high up for you to reach.\n");

    add_exit("dc2", "south");

    DARK;
    INSIDE;

    reset_room();
}
