/*
 * e2.c
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
    set_short("edge of a volcano");
    set_long("You are standing on the edge of a huge volcano. To the " +
             "southwest you see the boiling lake of lava. You think that " +
             "something is standing in the middle of the lake, but from " +
             "this distance you are not sure, because the steam from the " +
             "volcano keeps you from seeing very far.\n");

    add_exit("e1", "west");
    add_exit("e3", "south");
}
