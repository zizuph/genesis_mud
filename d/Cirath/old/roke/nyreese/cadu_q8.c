/*
 * cadu_q8.c
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
    set_short("Town square");
    set_long("You are at the town square in Cadu.\n" +
             "In the south you detect something emitting an " +
             "aura of very powerful magic, and to the north " +
             "a small alley leads towards the mighty castle.\n");
    
    add_exit("cadu_q5", "south");
    add_exit("cadu_q7", "west");
    add_exit("cadu_a2", "north");
    add_exit("cadu_q9", "east");
}
