/*
 * cas_t43.c
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

void reset_room();

void
create_room()
{
    set_short("Castle in Cadu");
    set_long("You are at the top of the southwest tower. Surrounding you, " +
             "is a ring of huge stones, protecting the guard from arrows " +
             "and preventing the painful death which would be the result " +
             "of falling from the tower and hitting the ground far below " +
             "you. Judging from the layer of clouds below you, you must " +
             "be standing quite high up in the air.\n");

    add_item("surroundings",
             "Below you to the south is the small town of Cadu, and when " +
             "you look to the southwest you feel the powerful magic of Roke " +
             "very far away.\n");

    add_item(({"cloud", "clouds"}), "The clouds are white and fluffy.\n");
    INSIDE;

    add_exit("cas_t33", "down");
    reset_room();
}

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
