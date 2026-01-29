/*
 * cas_b3.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/*  Ged & Gresolle */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"
#include <macros.h>

object knight;

void reset_room();

void
create_room()
{
    set_short("Castle in Cadu");
    set_long("You are standing beside a large stair leading upwards " +
             "to the third floor and downwards to the first floor. " +
             "The stairs are covered by a thick red mat.\n");

    add_item(({"mat", "red mat", "thick mat", "thick red mat"}),
             "This heavy mat efficiently subdues every sound of your footsteps.\n");

    add_exit("cas_b4", "east");
    add_exit("cas_b2", "west");
    add_exit("cas_c3", "up", "@@block");
    add_exit("cas_a3", "down", "@@block");
    INSIDE;

    reset_room();
}

void
reset_room()
{
    if (MAL("guard"))
        return;

    knight = clone_object(ROKEDIR + "npc/sknight2");
    knight->equip_me();
    knight->move(TO);
}

int
block()
{
    if (MAL("guard") && !TP->query_invis())
    {
        say(QCTNAME(TP) +
            " tries to enter the stairs but is stopped by the guard.\n");
        write("You are stopped by the guard.\n");
        return 1;
    }
    return 0;
}
