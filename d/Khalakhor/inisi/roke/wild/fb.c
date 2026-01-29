/*
 * fb.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 * Allowed sneaking by guard - Tapakah, July 2011.
 *
 * Updated to an abandoned camp with the Golbar camp moved to a new position, Treacher 08/2021
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


void
create_room()
{
    init_sp_quest();

    set_short("Forest");
    set_long("You are standing in a small clearing in the forest. In the " +
             "middle of it is a tiny pond, formed by a stream that runs " +
             "from the east. An old, partly collapsed barricade stands just " +
             "to the southeast.\n");

    add_item(({"barricade", "structure"}),
             "The barricade looks abandoned and parts of the structure has collapsed. " +
             "At some point in time it was probably well maintained, and was built "+
             "to protect something southeast from here.\n");

    add_item(({"pond", "water", "stream"}),
            "The small stream carries fresh water that collects in the tiny pond. " +
            "It looks clear enough to even drink some.\n");
    TREES;
    TREE2;
    GRASS;

    BEACH;

    add_cmd_item("water", "drink", "Ah, feels good.\n");

    add_exit("f7", "west");
    add_exit("fd", "southeast");

}

void
init()
{
    ::init();

    initrc();
}
