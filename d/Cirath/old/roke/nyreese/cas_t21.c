/*
 * cas_t21.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/*  Ged  & Gres */

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
    set_long("You are in the northwest tower of the castle. There is a " +
             "small window here overlooking the island of Nyreese.\n");

    add_item("window", "You can look through it.\n");
    add_cmd_item(({"window", "through window"}), "look",
                 "The only thing you see is the high mountains in the " +
                 "centre of the island. The rest is covered with thick fog.\n");

    INSIDE;
    add_exit("cas_b1", "southeast");
    reset_room();
}

void
reset_room()
{
    if (knight)
        return;

    tell_room(TO, "A guard arrives.\n");
    knight = clone_object(ROKEDIR + "npc/towerg2");
    knight->equip_me();
    knight->move(TO);
}
