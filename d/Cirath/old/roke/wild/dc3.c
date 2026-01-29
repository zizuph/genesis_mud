/*
 * dc3.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

void
create_room()
{
    set_short("entrance of cave");
    set_long("You are in the entrance of a huge cave. The path leads back " +
             "to the west, and if you go north you will enter the foul " +
             "smelling cave.\n");

    INSIDE;

    add_exit("d4", "west");
    add_exit("dc2", "north");

    add_item("cave", "@@cave");
}

string
cave()
{
    seteuid(getuid(TO));

    (WILDDIR + "dc2")->query_name();
    if (present("dragon", find_object(WILDDIR + "dc2")))
        return "You can see something moving in there.\n";
    return "The cave looks black and forbidding.\n";
}
