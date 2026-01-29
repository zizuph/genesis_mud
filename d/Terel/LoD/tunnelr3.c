/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * tunnelr3.c
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
    add_exit(LOD_DIR + "tunnelr4", "west",  0);
    add_exit(LOD_DIR + "tunnelr2b", "east", 0);
}
