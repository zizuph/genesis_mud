/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * path_a3.c
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
    add_my_desc("The path leads north-west.\n");
   
    add_exit(ENCHANT_DIR + "path_a2", "north", 0);
    add_exit(ENCHANT_DIR + "path_a4", "west",  0);
    add_exit(MAZE,                    "south", 0);
    add_exit(MAZE,                    "east",  0);
}

