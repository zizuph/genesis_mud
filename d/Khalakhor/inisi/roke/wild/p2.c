/*
 * p2.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit "/std/room";
inherit ROKEDIR + "lib/roomcode";

object t1, t2;

void reset_room();

void
create_room()
{
    init_sp_quest();

    set_short("troll settlement");
    set_long("You have stumbled upon a troll settlement. Around you " +
             "are lots of bones and disgusting gooey puddles of troll " +
             "excrements, that make this place smell worse than rotten " +
             "fish.\n");

    add_item("bones", "They have been chewed on.\n");
    add_item("puddles", "They look very disgusting.\n");

    add_exit("p1", "west");
    add_exit("p3", "north");

    reset_room();
}

void
reset_room()
{
    if (t1 || t2)
        return;

    t1 = clone_object(ROKEDIR + "npc/troll");
    t1->equip_me();
    t2 = clone_object(ROKEDIR + "npc/troll");
    t2->equip_me();

    t1->move(TO);
    t2->move(TO);

    t1->team_join(t2);
}

void
init()
{
    ::init();
    initrc();
}
