/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * tunnelr5.c
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
    add_exit(LOD_DIR + "tunnelr5", "east", 0);
    add_exit(LOD_DIR + "tunnelr5b", "west", 0);
    reset_room();
}
