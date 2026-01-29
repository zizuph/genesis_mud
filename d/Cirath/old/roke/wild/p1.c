/*
 * p1.c
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
    set_short("disgusting path");
    set_long("You are on a small path in the mountains, between some huge " +
             "rocks. Bones and leftovers from dead animals and perhaps also " +
             "a few unfortunate adventurers are stashed beside the path.\n");

    add_exit("r3", "north");
    add_exit("p2", "east");

    add_item("bones", "Someone has chewed on them.\n");
    add_item("leftovers", "Yuk! They stink!\n");
    add_item("rocks", "The boulders are approximately three meters high.\n");
}
