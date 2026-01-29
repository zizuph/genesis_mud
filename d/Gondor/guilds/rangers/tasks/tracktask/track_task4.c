/*
 *  /d/Gondor/guilds/rangers/hq/track_task4.c
 *
 *  A room for the rabbit tracking apprentice task
 *
 *  Coded by Alto, 07 December 2002
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include "../../rangers.h"

inherit TRACKTASK_DIR + "tracktask_funcs.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

void
create_gondor()
{
    set_short("A bend in the path");
    set_long("You have reached a bend in the forest path which runs "
        + "to the west and to the north. The corner of the bend seems "
        + "recently disturbed.\n");

    track_add_items();
    
    add_item(({"bend", "corner", "path"}), "The path here bends from "
        + "the north to the west. In its corner, however, you see that "
        + "the ground has been recently disturbed. On closer inspection "
        + "you see that the path also has a fork heading south.\n");

    add_exit(TRACKTASK_DIR  + "track_task3",   "south", &allowed(), 1, 1);
    add_exit(TRACKTASK_DIR  + "track_task6",   "north", &allowed(), 1);
    add_exit(TRACKTASK_DIR  + "track_task7",   "west", &allowed(), 1);

    reset_room();
}
