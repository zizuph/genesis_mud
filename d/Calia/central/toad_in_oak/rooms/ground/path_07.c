/* 
 * /d/Calia/central/toad_in_oak/rooms/ground/path_07.c
 *
 * A path on the northern edge of TiO, near the enterance to the village
 * 
 * HISTORY: 2003-05-11 Created by Kcirderf
 *
 * Copyright: Sean Dunphy (Kcirderf) 2003
 */ 

// INCLUSIONS AND DEFINITIONS

inherit "/d/Calia/central/toad_in_oak/rooms/ground/baseroom_ground.c";

#include <stdproperties.h>
#include "defs.h"

// ROOM DEFINITION

void
create_tio_ground_room()
{
    set_short("A path beneath a village in the trees.");    
    set_long("Your are surrounded by the immense oaks that make up " +
        "this part of the forest, their leaves covering the ground with " +
        "green shadows. A village has been built into their branches high " +
        "above. Between their trunks the ground is covered by a thick " + 
        "carpet of green grass.\n"); 
    
    add_item(Grass_Words, grass_describe(({"north", "southwest"}))); 
    add_item(Tree_Words, trees_describe(0, "")); 
    add_item(Village_Words, village_describe()); 

    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "path_08", "north"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "path_06", "southwest"); 
}
