/*
 * ohut.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/* A maze-forest north of Cadu  */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

void
create_room()
{
    set_short("Outside a hut");
    set_long("You are outside an old hut. Although it is a very " +
             "old hut it somehow has managed to stay in reasonably " +
             "good condition, and you realize that someone must " +
             "be maintaining it and perhaps also living in it.\n");

    add_exit("ran/for2", "south");

    add_exit("ihut", "in", "@@block");

    OUTSIDE;
}

int
block()
{
    if (TP->query_prop("_enemy_of_ogion"))
    {
        TP->catch_msg("You are stopped by some powerful magic.\n");
        return 1;
    }
    return 0;
}
