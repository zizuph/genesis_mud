/*
 * red_r2.c
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
    set_short("on a small road");
    set_long("This is a small road leading past some buildings. " +
             "North of you is the local brewery delivering drinks " +
             "to the pub, and further west you can spot the " +
             "local cathouse.\n");

    add_exit("red_brewery", "north");
    add_exit("red_r3", "east");
    add_exit("red_r1", "west");
}
