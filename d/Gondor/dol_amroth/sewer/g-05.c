/* -*- Mode: C -*-
 * Sewer g-05.c
 */
#include "../defs.h"

inherit DOL_STD+"sewer";
inherit "/lib/unique";

int
sea_block()
{
    write("A grate blocks your path northeast.\n");
    return 1;
}

void
create_sewer()
{
    set_grate("up", DOL_COMMON + "streets/g-05");
    add_exit(DOL_SEWER + "g-06", "south", 0, 2);
    add_exit(DOL_SEWER + "h-04", "northeast", &sea_block(), 2);
    reset_room();
}

void
reset_room()
{
    clone_unique(DOL_NPC + "assassin", 1, 0, 1);
}
