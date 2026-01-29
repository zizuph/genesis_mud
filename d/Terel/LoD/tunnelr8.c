/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * tunnel5.c
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
    add_exit(LOD_DIR + "guard_room3", "south",   0);
    add_exit(LOD_DIR + "tunnelr7b",    "east",   0);
}
