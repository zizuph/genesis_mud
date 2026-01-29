/*
 * d1.c
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
    set_short("small path");
    set_long("You are on a small path leading upwards to a small plateau " +
             "between some mountains. Occasionaly a few stones fall down " +
             "from the cliffs, but otherwise it is very quiet here.\n");

    add_exit("r1", "south");
    add_exit("d2", "north");
}
