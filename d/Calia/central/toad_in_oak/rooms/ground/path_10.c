/* 
 * /d/Calia/central/toad_in_oak/rooms/ground/path_10.c
 *
 * A path on the western edge of TiO, near the green
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
    set_long("From where you stand now you can see that the space " + 
        "between the dense wall of vegetaion to the west and the " + 
        "babbling stream to the east widens to the south, forming " +
        "a large clearing. High above there is a village built into the " +
        "branches of the immense oak trees that surround you. Lush " + 
        "grash covers the ground between the tree trunks, the stream, " +
        "and the thicket.\n");       
 
    add_item(Grass_Words, grass_describe(({"southeast", "south", "northwest"}))); 
    add_item(Stream_Words, stream_describe()); 
    add_item(Thicket_Words, thicket_describe("west")); 
    add_item(Tree_Words, trees_describe(1, "northeast")); 
    add_item(Village_Words, village_describe()); 

    add_item(({"clearing", "green"}), "To the south there is a large area " + 
        "between the thicket and the stream that is devoid of trees, " + 
        "probably some sort of village green. In the center of the " + 
        "clearing there is some sort of wooden structure.\n"); 
    
    add_item(({"structure", "gazebo"}), "You cannot make out the structure " +
        "in the clearing in any great detail, but it appears to be a sort " + 
        "of gazebo.\n"); 

    stream_tells(); 
    thicket_tells(); 

    add_prop(OBJ_I_CONTAIN_WATER, -1); 
   
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "green_ne", "southeast"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "green_nw", "south"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "path_09", "northwest"); 
}

void
init()
{
    ::init(); 

    add_action(stream_drink, "drink"); 
}

