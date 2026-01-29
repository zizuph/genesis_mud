/*
 * cas_t11.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/*  Ged  & Gresolle */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

void reset_room();

void
create_room()
{
    set_short("Castle in Cadu");
    set_long("You are in the northwest tower. It's a circular " +
             "room built in the same material as the rest of the " +
             "castle, damp, cold, grey stone. There is a window " +
             "in the wall, letting some light in.\n");

    add_exit("cas_a1", "southeast");

    add_item("window", "You can look through it.\n");
    add_cmd_item(({"window", "through window"}), "look",
                 "You see the vast mountains of Nyreese.\n");
    INSIDE;
    reset_room();
}

void
reset_room()
{
    if (MAL("guard"))
        return;

    clone_object(ROKEDIR + "npc/towerg1")->move(TO);
    tell_room(TO, "The tower guard arrives.\n");
}
