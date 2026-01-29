/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * forest14.c
 *
 */

#include "/d/Terel/include/Terel.h"
inherit ENCHANT_DIR + "forest_room";

#include "enchanted.h"

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    add_exit(MAZE, "south", 0, HARD_TO_WALK);
    add_exit(MAZE, "west",  0, HARD_TO_WALK);
    add_exit(MAZE, "east",  0, HARD_TO_WALK);
    add_exit(MAZE, "north", 0, HARD_TO_WALK);
}

