/* 
 * /d/Calia/central/toad_in_oak/rooms/ground/path_11.c
 *
 * A path on the southern edge of TiO, near the green
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
    set_long("You stand among the colossal oak trees that make up this " + 
        "part of the forest, and can see the underside of a village in " + 
        "their branches overhead. Shifting green shadows cover the carpet " + 
        "of grass on the ground, which opens into a large clearing to the " + 
        "northwest. A dense thicket of brush blocks the way south.\n"); 

    add_item(Grass_Words, grass_describe(({"east", "northwest"}))); 
    add_item(Thicket_Words, thicket_describe("south")); 
    add_item(Tree_Words, trees_describe(1, "north")); 
    add_item(Village_Words, village_describe()); 
   
    add_item(({"clearing", "green"}), "To the south there is a large area " + 
        "between the thicket and the stream that is devoid of trees, " + 
        "probably some sort of village green. In the center of the " + 
        "clearing there is some sort of wooden structure.\n"); 
    
    add_item(({"structure", "gazebo"}), "You cannot make out the structure " +
        "in the clearing in any great detail, but it appears to be a sort " + 
        "of gazebo.\n"); 

    thicket_tells(); 

    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "path_12", "east"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "green_se", "northwest"); 
}
