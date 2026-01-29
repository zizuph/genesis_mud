/*
 * f5.c
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
    set_short("On a mountain side");
    set_long("You have walked into a small opening in the forest, that " +
             "reveals the huge volcano that resides in the middle of the " +
             "island. Huge boulders block most of the side, but between " +
             "two of them you can see a path leading up to the top.\n");

    add_item(({"boulder", "boulders"}), "The boulders are huge.\n");

    add_exit("p", "up");
    add_exit("f3", "north");
    add_exit("f7", "south");
}
