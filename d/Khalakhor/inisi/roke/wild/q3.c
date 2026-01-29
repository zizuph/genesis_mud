/*
 * q3.c
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
    set_short("a very steep cliff");
    set_long("This is a very steep cliff. You are holding " +
             "yourself tightly by some stones and when " +
             "you look down you notice that it is a very " +
             "long way down there.\n");

    add_exit("tp", "up");
    add_exit("q2", "south", -2, 5);
}
