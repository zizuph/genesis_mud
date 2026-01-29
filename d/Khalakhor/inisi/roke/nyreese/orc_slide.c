/*
 * orc_slide.c
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
    set_long("You are standing just below a slide, with which the orc " +
             "children play when they are at the orc kindergarten.\n");
    set_short("orc slide");
    add_exit("orc_play", "west");
    add_item("slide", "It's a small slide, too small for you to use it.\n");
    reset_room();
}

void
reset_room()
{
    int t, n;
    object ob;

    tell_room(TO, "Some orcs arrive from the forest.\n");

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
}
