/*
 * orc_play.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/* Gresolle 1992 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

void reset_room();

void
create_room()
{
    set_short("orc playground");
    set_long("You have stumbled upon a small area in the forest that " +
             "obviously is used as a playground by orc children. All " +
             "around you are various toys and playing equipment, and " +
             "to the north is the entrance to a small building, " +
             "which obviously is used by the local orc kindergarten.\n");

    add_exit("orc_road2", "south");
    add_exit("orc_sand", "west");
    add_exit("orc_slide", "east");
    add_exit("orc_house", "enter");
    reset_room();
}

void
reset_room()
{
    int t, n;
    object ob;

    n = 1 + random(2);
    for (t = 0; t < n; t++)
        clone_object(ROKEDIR + "npc/orc1")->move(TO);

    n = 1 + random(3);
    for (t = 0; t < n; t++)
    {
        ob = clone_object(ROKEDIR + "npc/orc2");
        ob->equip_me();
        ob->move(TO);
    }

    tell_room(TO, "A few orc children comes from the house.\n");
}
