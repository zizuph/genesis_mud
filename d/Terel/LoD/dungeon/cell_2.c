/*
 * cell_2.c
 *
 * A dungeon below the Legion of Darkness quarters.
 */

#include "/d/Terel/include/Terel.h"
inherit LOD_DIR + "/dungeon/cell";

#include <stdproperties.h>
#include <macros.h>

public string*
query_moving_object_list()
{
    return ({LOD_DIR + "monster/ogre"});
}

public void
create_room()
{
    ::create_room();
    
    reset_room();
}
