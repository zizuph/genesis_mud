/*
 * f7.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/* ged */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

void
create_room()
{
    set_short("Forest");
    set_long("You are standing in the middle of the forest. To the north " +
             "you can see quite a lot of grass, and east of here you think " +
             "that you see a small area of water, reflecting the sunlight.\n");

    add_exit("f8", "north");
    add_exit("fb", "east");
    add_exit("f6", "southwest");
}
