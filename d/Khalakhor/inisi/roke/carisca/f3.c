/*
 * f3.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

object s1, s2, s3, s4;

void
reset_room()
{
    tell_room(this_object(), "The sheep says Baaaahhh!\n");
    if (!s1)
    {
        s1 = clone_object(ROKEDIR + "npc/sheep");
        s1->move(TO);
    }
    if (!s2)
    {
        s2 = clone_object(ROKEDIR + "npc/sheep");
        s2->move(TO);
    }
    if (!s3)
    {
        s3 = clone_object(ROKEDIR + "npc/sheep");
        s3->move(TO);
    }
    if (!s4)
    {
        s4 = clone_object(ROKEDIR + "npc/sheep");
        s4->move(TO);
    }
}

void
create_room()
{
    set_short("Forest on Carisca island");
    set_long("The forest around you is quite dark and damp. The " +
             "trees seem to reach out for you and you hear the " +
             "mating roars of the wild boars in the distance.\n");

    add_exit("f2", "west");
    add_exit("f5", "south");

    reset_room();
}
