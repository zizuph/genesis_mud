/*
 * d3.c
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
    set_short("path intersection");
    set_long("This is an intersection between three paths. The eastern " +
             "path seems to lead to a huge cave, and when you look west " +
             "you spot some kind of building close to the mountainside.\n");

    add_item("building", "It looks like some kind of temple.\n");
    add_item("cave",
             "This is a very impressive cave, large enough to contain an entire ship.\n");

    add_exit("d4", "east");
    add_exit("d5", "west");
    add_exit("d2", "south");
}
