/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * path_a1.c
 *
 */

#include "/d/Terel/include/Terel.h"
inherit ENCHANT_DIR + "path_room";

#include "enchanted.h"

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    add_my_desc("The path leads north-south.\n");
   
    add_exit(ENCHANT_DIR + "n_edge3", "north", 0);
    add_exit(ENCHANT_DIR + "path_a2", "south", 0);
    add_exit(MAZE,                    "east",  0);
    add_exit(MAZE,                    "west",  0);
   
}

