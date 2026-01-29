/*
 * cas_t31.c
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
    set_long("You are in the northwest tower. There is a small ladder " +
             "leading upwards to the roof of the castle, and in the " +
             "outside wall is a narrow window.\n");
    add_item("window",
             "The window leads outside towards some uninteresting trees.\n");

    add_cmd_item(({"window", "through window"}), "look",
                 "The window leads outside towards some uninteresting trees.\n");

    add_item("trees", "They are green, beautiful and VERY old.\n");
    add_item("ladder", "A small, unsafe, wooden ladder.\n");

    add_exit("cas_c1", "southeast");
    add_exit("cas_t41", "up", "@@block");
    INSIDE;

    reset_room();
}

void
reset_room()
{
    if (knight)
        return;

    tell_room(TO, "The guard arrives.\n");

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
