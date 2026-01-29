/*
 * cas_t22.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/*  Ged  & gresolle */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

object knight;

void reset_room();

void
create_room()
{
    INSIDE;
    set_short("Castle in Cadu");
    set_long("You are in the northeast tower of the castle. Unlike most " +
             "of the other tower rooms this one has no window. Instead it " +
             "is illuminated by a large torch high up on one of the walls.\n");

    add_item("torch",
             "It is a very large torch. It will most likely burn for days.\n");
    add_cmd_item("torch", "take",
                 "You are too short. It is unreachable for you!\n");
    add_cmd_item("torch", "get",
                 "You are too short. It is unreachable for you!\n");

    add_exit("cas_b4", "southwest");

    INSIDE;
}

void
reset_room()
{
    if (knight)
        return;

    tell_room(TO, "A nasty-looking guard arrives.\n");
    knight = clone_object(ROKEDIR + "npc/towerg2");
    knight->equip_me();
    knight->move(TO);
}
