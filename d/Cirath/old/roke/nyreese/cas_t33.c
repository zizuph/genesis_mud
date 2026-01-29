/*
 * cas_t33.c
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
    set_long("This is a small room in the tower. Above you is the lookout, " +
             "which you can reach by climbing the small wooden ladder that " +
             "is placed in the middle of the room.\n");

    add_item("ladder",
             "It's a small ladder, made of wood. It looks very old.\n");
    add_exit("cas_c9", "northeast");
    add_exit("cas_t43", "up", "@@block");
    INSIDE;
    reset_room();
}

void
reset_room()
{
    if (knight)
        return;

    tell_room(TO, "You feel slightly uncomfortable as the guard arrives.\n");

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
