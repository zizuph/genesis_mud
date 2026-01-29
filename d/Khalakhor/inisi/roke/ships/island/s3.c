/*
 * s3.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "../../defs.h"

void
create_room()
{
    set_short("Beach");
    set_long("You are swimming in the water very close to the beach. " +
             "There are very loud " +
             "noises coming from the small mountain east of the beach.\n");

    add_exit("i1", "east");

    WATER;
}

void
init()
{
    ::init();
    add_action("swim", "swim");
}

int
swim(string s)
{
    NF("You think it might be too dangerous to swim any more.\n" +
       "You feel that it must be safer to get on to the beach.\n");
    if (s != "east")
        return 0;

    write("It's very hard to swim when there is almost no water!\n");
    return 1;
}
