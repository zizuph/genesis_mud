/*
 * sea5.c
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
    set_short("Sea");

    set_long("You are in the open sea. To the east you can see a small " +
             "island. You can also hear some sounds from the island.\n");
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
    NF("You think it might be too dangerous to swim in that direction.\n");
    if (s != "east")
        return 0;

    TP->move_living("east", SHIPDIR + "island/s1");
    return 1;
}
