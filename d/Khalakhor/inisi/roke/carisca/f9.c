/*
 * f9.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

void
create_room()
{
    set_short("Forest edge");
    set_long("South of you is the open sea, limited only by the horizon. " +
             "A small path leads along the shore, towards the great forest " +
             "that covers most of the island, except for the volcano top.\n");

    add_item("sea", "The sea looks very calm today.\n");

    add_exit("f10", "east");
    add_exit("f8", "west");
}
