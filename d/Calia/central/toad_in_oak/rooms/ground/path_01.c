/* 
 * /d/Calia/central/toad_in_oak/rooms/ground/path_01.c
 *
 * A path on the western edge of TiO, at the enterance to the village
 * 
 * HISTORY: 2003-05-10 Created by Kcirderf
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
    set_long("You stand among the immense oaks that dominate this part " + 
        "of the forest, their leaves covering the ground with shifting " +
        "shadows. In the branches far above you can see the underside of " +
        "a village built into the trees. Grass covers the ground here " + 
        "like a thick green carpet. A stream winds it's way through the " +
        "forest just to the north, and there is a dense thicket " + 
        "blocking passage to the south, and another just beyond the " + 
        "stream.\n"); 
    
    add_item(Grass_Words, grass_describe(({"east", "west"}))); 
    add_item(Stream_Words, stream_describe()); 
    add_item(Thicket_Words, thicket_describe("south and on the far " + 
        "side of the stream")); 
    add_item(Tree_Words, trees_describe(0, "")); 
    add_item(Village_Words, village_describe()); 

    add_prop(OBJ_I_CONTAIN_WATER, -1); /* Infinite water from the stream */
    
    stream_tells(); 
    thicket_tells();  

    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "path_02", "east"); 
}

void 
init()
{
    ::init(); 
        
    add_action(stream_drink, "drink"); 
    
}

void
hook_smelled(string smelled)
{
    common_smells(smelled);
}

