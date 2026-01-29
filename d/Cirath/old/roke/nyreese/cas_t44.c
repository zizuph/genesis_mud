/*
 * cas_t44.c
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
    set_long("You are at the top of the southeast tower. Surrounding you, " +
             "is a ring of huge stones, protecting the guard from arrows " +
             "and preventing the painful death which would be the result " +
             "of falling from the tower and hitting the ground far below " +
             "you. Judging from the layer of clouds below you, you must " +
             "must be standing quite high up in the air.\n");

    add_item("surroundings",
             "Looking far to the southeast you only see the open sea.\n");
    INSIDE;
    add_item(({"cloud", "clouds"}), "The clouds are white and fluffy.\n");

    add_item("stones", "The stones are there to protect the guards " +
             "from arrows.\n");
    add_item("ring", "The ring consists of twelve huge stones.\n");

    add_exit("cas_t34", "down");
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
