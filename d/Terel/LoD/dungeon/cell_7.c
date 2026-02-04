/*
 * cell_x.c
 *
 * A dungeon below the Legion of Darkness quarters.
 */

#include "/d/Terel/include/Terel.h"
inherit LOD_DIR + "/dungeon/cell";

#define DUNG_DIR (LOD_DIR + "dungeon/")

public string*
query_moving_object_list()
{
    return ({LOD_DIR + "monster/wolf"});
}

public void
create_room()
{
    ::create_room();
    
    reset_room();
}
