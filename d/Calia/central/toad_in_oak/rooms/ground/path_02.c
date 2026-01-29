/* 
 * /d/Calia/central/toad_in_oak/rooms/ground/path_02.c
 *
 * A path on the western edge of TiO, near the enterance to the village
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
    set_long("You are surrounded by the trunks of the gargantuan oaks " + 
        "that make up this part of the forest. Far above you see the " + 
        "underside of a small village supported by the branches of the " + 
        "trees. Thick green grass covers the ground here between the " + 
        "stream flowing by just to the north and the dense thicket to " +
        "the south.\n"); 

    add_item(Grass_Words, grass_describe(({"east", "west"}))); 
    add_item(Stream_Words, stream_describe()); 
    add_item(Thicket_Words, thicket_describe("south and on the far " + 
        "side of the stream")); 
    add_item(Tree_Words, trees_describe(0, "")); 
    add_item(Village_Words, village_describe()); 

    add_prop(OBJ_I_CONTAIN_WATER, -1); /* Infinite water from stream */ 
    
    stream_tells(); 
    thicket_tells(); 

    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "path_01", "west"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "path_03", "southeast"); 
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

