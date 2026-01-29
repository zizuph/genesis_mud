/*
 * cas_t42.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
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
    set_long("You are at the top of the northeast tower. Surrounding you, " +
             "is a ring of huge stones, protecting the guard from arrows " +
             "and preventing the painful death which would be the result " +
             "of falling from the tower and hitting the ground far below " +
             "you. Judging from the layer of clouds below you, you must " +
             "be standing quite high up in the air.\n");
    INSIDE;

    add_item("surroundings", "You look at the northeast parts of Nyreese.\n" +
             "Unfortunately, those parts haven't been created yet so " +
             "there's not much to see.\n");
    add_item(({"cloud", "clouds"}), "The clouds are white and fluffy.\n");

    add_exit("cas_t32", "down");
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
