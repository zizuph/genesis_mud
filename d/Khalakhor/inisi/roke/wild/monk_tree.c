/*
 * monk_tree.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

//MUPP, do something with this place?

void
create_room()
{
    set_short("Up in a high tree");
    set_long("You are high up among the branches of a huge tree.\n");

    add_exit("p6", "down");
}
