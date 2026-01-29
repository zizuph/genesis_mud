/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * tunnelr7.c
 *
 * A tunnel in LoD.
 */

#include "/d/Terel/include/Terel.h"
inherit LOD_DIR + "tunnelr";

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    add_exit(LOD_DIR + "guard_room2", "south",   0);       
    add_exit(LOD_DIR + "tunnelr6b",    "east",   0);
    add_exit(LOD_DIR + "tunnelr7a",    "west",   0);
}
