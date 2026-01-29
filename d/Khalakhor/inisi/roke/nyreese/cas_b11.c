/*
 * cas_b11.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/*  Gres! */

/* gogge ged had put inherit after object ukk... */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

object knight1, knight2, knight3;

void
reset_room()
{
    if (knight1 || knight2 || knight3)
        return;

    knight1 = clone_object(ROKEDIR + "npc/guard2");
    knight1->equip_me();
    knight1->move(TO);
    knight2 = clone_object(ROKEDIR + "npc/guard2");
    knight2->equip_me();
    knight2->move(TO);
    knight3 = clone_object(ROKEDIR + "npc/guard2");
    knight3->equip_me();
    knight3->move(TO);
}

void
create_room()
{
    set_short("Level 2 guardroom");
    set_long("This is the second guard room in the castle.\n" +
             "Usually it's empty, but now it seems like you have " +
             "stumbled right in on the lunchbreak of the guards...\n");

    add_exit("cas_b12", "east");

    reset_room();
}
