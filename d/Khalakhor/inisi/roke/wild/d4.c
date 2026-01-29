/*
 * d4.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

string
cave()
{
    seteuid(getuid(TO));

    (WILDDIR + "dc2")->query_name();
    if (present("dragon", find_object(WILDDIR + "dc2")))
        return "You barely see something moving in there.\n";
    return "The cave looks black and forbidding.\n";
}

void
create_room()
{
    set_short("small path");
    set_long("You are on a small path between some bushes. The air is " +
             "very clear here, and you can see some smoke to the south" +
             "west, most likely from the chimneys of Cadu. East of you " +
             "is the entrance of a huge cave.\n");

    add_item("smoke", "It is white.\n");
    add_item("bushes",
             "The bushes have thorns, and their berries looks uneatable.\n");
    add_item("cave", "@@cave");

    add_exit("dc3", "east");
    add_exit("d3", "west");
}
