/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * tunnel9.c
 *
 * A tunnel in LoD.
 */

#include "/d/Terel/include/Terel.h"
inherit LOD_DIR + "tunnel";

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    add_exit(LOD_DIR + "tunnel10e", "north", 0);
    add_exit(LOD_DIR + "tunnel10c",  "south",  0);
    reset_room();
}
