/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * path_a5.c
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
    add_my_desc("The path leads west-east.\n");
   
    add_exit(ENCHANT_DIR + "path_a4", "east",  0);
    add_exit(ENCHANT_DIR + "path_a6", "west",  0);
    add_exit(MAZE,                    "south", 0);
    add_exit(MAZE,                    "north", 0);
}

