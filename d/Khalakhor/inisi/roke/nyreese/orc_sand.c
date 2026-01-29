/*
 * orc_sand.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/* Gresolle 1992 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

inherit ROKEDIR + "lib/roomcode";

void reset_room();

void
create_room()
{
    init_sp_quest();

    set_long("You are standing in the middle of a sand box, used " +
             "by the orc children to play in.\n");

    set_short("orc sandbox");
    add_exit("orc_play", "east");
    reset_room();
}

void
reset_room()
{
    int t, n;
    object ob;

    tell_room(TO, "Some orc children come crawling.\n");

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

void
init()
{
    ::init();
    initrc();
}
