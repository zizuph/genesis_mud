/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * n_edge1.c
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
    add_exit(ENCHANT_DIR + "n_edge2", "northwest", 0);
    add_exit(MAZE,                    "south",     0);
}

