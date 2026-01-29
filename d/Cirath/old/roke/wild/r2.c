/*
 * r2.c
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
    set_short("on a road in a forest");
    set_long("This is a well-travelled road leading east-west from here. " +
             "To the north is a thick forest, and above the treetops you " +
             "see a few mountains very far away. South of you is a small " +
             "path leading deeper into the forest.\n");

    add_exit("r3", "east");
    add_exit("r1", "west");
    add_exit("sh1", "south");
}
