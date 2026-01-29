/*
 * fe.c
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
    set_short("High cliff");
    set_long("You are standing on the edge of a high cliff. Down there you " +
             "can hear a woodpecker pecking on a tree. Further south you see " +
             "the village Cadu with the big castle shining in the sun. " +
             "The small track continues northeast and northwest.\n");

    add_exit("ff", "northeast");
    add_exit("f6", "northwest");
}
