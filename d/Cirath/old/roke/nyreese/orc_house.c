/*
 * orc_house.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/* Gresolle 1992 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

object teacher;

void reset_room();

void
create_room()
{
    INSIDE;

    set_short("orc kindergarten");
    set_long("You are inside the orc kindergarten. The walls around " +
             "you are covered by childrens paintings and on the floor " +
             "are lots of toys piled upon each other.\n");

    add_item("toys", "Someone has chewed on them.\n");
    add_item("paintings",
             "The paintings show different ways to kill humans.\n");
    add_exit("orc_play", "out");
    reset_room();
}

void
reset_room()
{
    object ob;
    tell_room(TO, "Some orcs enter the building.\n");

    if (!teacher)
    {
        teacher = clone_object(ROKEDIR + "npc/orc3");
        teacher->move(TO);
    }

    clone_object(ROKEDIR + "npc/orc1")->move(TO);
    clone_object(ROKEDIR + "npc/orc1")->move(TO);
    clone_object(ROKEDIR + "npc/orc1")->move(TO);
    ob = clone_object(ROKEDIR + "npc/orc2");
    ob->equip_me();
    ob->move(TO);
    ob = clone_object(ROKEDIR + "npc/orc2");
    ob->equip_me();
    ob->move(TO);
}
