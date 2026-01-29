/*
 * cas_a3.c
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

void
reset_room()
{
    object ob;
    if (MAL("guard")) return;

    ob = clone_object(ROKEDIR + "npc/sknight1");
    ob->equip_me();
    ob->move(TO); 

    /* sknight1 <=> StairKNIGHTlevel1 */
}

void
create_room() 
{
    set_short("Staircase");
    set_long("You are standing just below a huge stair leading upwards, " +
             "to the second floor of the castle.\n");
    INSIDE;
    add_exit("cas_a7", "south");
    add_exit("cas_b3", "up", "@@block");
    reset_room();
}

int
block()
{
    if (MAL("guard") && !TP->query_invis())
    {
        TP->catch_msg("You try to go up the stairs, but are stopped by " +
                      "the knight.\n");
        say(QCTNAME(TP) + " tries to move upstairs, but is stopped " +
            "by the guard.\n");
        return 1;
    }

    return 0;
}
