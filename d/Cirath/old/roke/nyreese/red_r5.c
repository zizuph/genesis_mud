/*
 * red_r5.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

object b1, b2, b3;

void
reset_room()
{
    if (!b1)
    {
        b1 = clone_object(ROKEDIR + "npc/bum");
        b1->equip_me();
        b1->move(TO);
    }
    if (!b2)
    {
        b2 = clone_object(ROKEDIR + "npc/bum");
        b2->equip_me();
        b2->move(TO);
    }
    if (!b3)
    {
        b3 = clone_object(ROKEDIR + "npc/bum");
        b3->equip_me();
        b3->move(TO);
    }
}

void
create_room()
{
    set_short("a filthy square");
    set_long("You have reached some kind of square, where the locals " +
             "sell their merchandise, drugs, weapons, and themselves. " +
             "As you look around, you wonder why they don't move. It " +
             "would be better to live under a tree in the nearby forests. " +
             "There is a small fire close to one of the buildings and " +
             "an open door to the west of you.\n" +
             "There are two obvious exits: north and south.\n");

    set_noshow_obvious(1);

    add_exit("red_h1", "west");
    add_exit("red_r4", "north");
    add_exit("red_jabroom", "south");

    reset_room();
}
