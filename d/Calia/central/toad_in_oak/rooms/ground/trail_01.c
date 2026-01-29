/* 
 * /d/Calia/central/toad_in_oak/rooms/ground/trail_01.c
 *
 * The beginning of the trail up the hill east of TiO
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
    set_short("Near the bottom of a hill in the forest."); 
    set_long("You stand near the bottom of a hill that rises out of the " + 
        "forest of giant oaks. Changing shadows cover the grass that grows " +
        "between the tree trunks, giving way to patches of brightly " + 
        "colored flowers at the bottom of the hill. You can see a village " + 
        "that has been built high in the branches of the trees just west " +
        "of here.\n"); 

    add_item(({"flowers"}), "At the bottom of the hill, just west of where " + 
        "you stand, there are a number of pathches of flowers of various " + 
        "types and colours. You are too far away to make out any details.\n"); 

    add_item(Grass_Words, trail_describe("southeast", "southwest")); 
    add_item(Hill_Words, hill_describe()); 
    add_item(Tree_Words, trees_describe(0, "")); 
    add_item(Village_Words, village_describe()); 

    add_tell("A butterfly flutters by, heading towards the flowers west " + 
        "of here.\n"); 
    add_tell("A bee buzzes past your ear on it's way home after a visit " +
        "to the flowers.\n"); 

    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "trail_02", "southeast"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "flowers_e", "southwest"); 
}
