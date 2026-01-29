/*
 * cas_t32.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/*  Ged & Gresolle  */

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
    set_long("You are in the northeast tower. The walls are damp, and " +
             "since there are no windows here the only source of light " +
             "is the small hole high above where the ladder leads to " +
             "the next floor of the tower.\n");

    add_item("ladder", "The ladder leads to the next floor of the tower.\n");
    add_exit("cas_c4", "southwest");
    add_exit("cas_t42", "up", "@@block");
    INSIDE;
    reset_room();
}

void
reset_room()
{
    if (knight)
        return;

    tell_room(TO, "A guard arrives and stares at you, with murder in his eyes.\n");

    knight = clone_object(ROKEDIR + "npc/towerg3");
    knight->equip_me();
    knight->move(TO);
}

int
block()
{
    if (knight)
    {
        write("You try to climb the ladder, but the guard stops you!\n");
        say(QCTNAME(TP) + " tries to climb the ladder, but is brutally " +
            "stopped by the guard.\n");
        return 1;
    }
    return 0;
}
