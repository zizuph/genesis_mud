/*
 * cas_dung1.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

object pris;

void
reset_room()
{
    if (pris)
        return;

    pris = clone_object(ROKEDIR + "npc/prisoner");
    pris->move(TO);
}

void
create_room()
{
    set_short("Dungeon");
    set_long("You are in what is left of the dungeons under the castle.\n" +
             "Many years of usage has set its marks on the walls, which " +
             "are covered with blood.\n");

    DARK;

    add_exit("cas_t14", "up");
    reset_room();
}
