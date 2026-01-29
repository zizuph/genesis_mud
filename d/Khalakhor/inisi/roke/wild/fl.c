/*
 * fl.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/* ged */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "forest.h"

void
create_room()
{
    set_short("Forest edge");
    set_long("This is the edge of the forest. You can see a small road " +
             "leading to the east and there are also lots of heavy footprints " +
             "on the ground. There is also a small sign on a wooden pole. " +
             "To the east you can spot some mountains in the distance " +
             "and to your west the trees form the rest of the forest.\n");

    TREES;
    TREE1;

    add_item("sign", "The road is closed until the attack is over !\n" +
             "Ogion the Silent.\n");
    add_cmd_item("sign", "read", "The road is closed until the" +
                 " attack is over !\nThe Mayor of Cadu.\n");

    add_exit("fm", "northwest");
    add_exit("fk", "south");
    //    add_exit("east", "east", "@@block");
}

int
block()
{
    write("The road is closed due to the invasion.\n");
    return 1;
}
