/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * n_edge3.c
 *
 */

#include "/d/Terel/include/Terel.h"
inherit ENCHANT_DIR + "n_edge_room";

#include "enchanted.h"

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
   
    add_my_desc("A small path leads south into the forest.\n");
    add_item("path", "It is small and hardly recognizable here.\n");

    add_exit(ENCHANT_DIR + "path_a1", "south", 0);
    add_exit(ENCHANT_DIR + "n_edge2", "east",  0);
    add_exit(ENCHANT_DIR + "n_edge4", "west",  0);
}

