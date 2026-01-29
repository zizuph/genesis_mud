/*
 * cas_t41.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/*  Ged  */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

object knight;

void
reset_room()
{
    if (knight)
        return;

    tell_room(TO, "A guard comes climbing up the ladder.\n");
    knight = clone_object(ROKEDIR + "npc/towerg4");
    knight->equip_me();
    knight->move(TO);
}

void
create_room()
{
    set_short("Castle in Cadu");
    set_long("You are at the top of the northwest tower. Surrounding you, " +
             "is a ring of huge stones, protecting the guard from arrows " +
             "and preventing the painful death which would be the result " +
             "of falling from the tower and hitting the ground far below " +
             "you. Judging from the layer of clouds below you, you must " +
             "be standing quite high up in the air.\n");
    INSIDE;

    add_item("surroundings",
             "To the northwest you see the high mountins of Nyreese.\n");

    add_item(({"cloud", "clouds"}), "The clouds are white and fluffy.\n");

    add_exit("cas_t31", "down");
    reset_room();
}
