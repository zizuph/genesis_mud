/*
 * f1.c
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
    set_short("outside a cave");
    set_long("You are just outside a small cave leading into the volcano.\n" +
             "A foul smell of sulphur and some strange noises comes from " +
             "the opening, and you think that something is moving inside.\n");
    
    add_exit("c2", "southeast", "@@block");
    add_exit("f2", "east");
    add_exit("f4", "south");
}

int
block()
{
    return this_player()->query_npc();
}
