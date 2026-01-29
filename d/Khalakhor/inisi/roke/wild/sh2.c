/*
 * sh2.c
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
    set_short("outside a small cave");
    set_long("You are in a small meadow, just below a mountain, outside " +
             "a small cave. There is really nothing special with this place, " +
             "except for the cave, but you notice the refuse that is scattered " +
             "around the cave.\n");

    add_item("refuse",
             "It's not usable for anything, unless you are interested in garbage.\n");

    add_exit("sh3", "east");
    add_exit("sh1", "north");
}
