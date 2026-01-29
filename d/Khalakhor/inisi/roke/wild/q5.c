/*
 * q5.c
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
    set_short("A beautiful mountain slope");
    set_long("You are walking on a beautiful path leading slightly " +
             "downwards from a high mountain top. The wind is blowing " +
             "lightly and it is getting rather cold rather quickly here.\n");

    add_exit("q4", "south", -3, 1);
    add_exit("q6", "east");
}
