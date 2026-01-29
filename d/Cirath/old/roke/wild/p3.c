/*
 * p3.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

void
create_room()
{
    set_short("mountain path");
    set_long("You are on a small mountain path. Huge boulders block all " +
             "movement to the north, but it is possible to go east or " +
             "west, along the path, or towards a bad smelling area in the " +
             "south.\n");

    add_item("boulders", "You wonder who put them there.\n");
    add_exit("p4", "east");
    add_exit("r3", "west");
    add_exit("p2", "south");
}
