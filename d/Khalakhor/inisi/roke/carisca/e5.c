/*
 * e5.c
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
    set_short("edge of volcano");
    set_long("You are standing on the edge of a boiling volcano.\n" +
             "To the northwest is the steaming crater, and in the " +
             "middle of it you think that you see a strange stone " +
             "pillar.\n");

    add_exit("e4", "west");
    add_exit("e3", "north");
}
