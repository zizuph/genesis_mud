/*
 * /d/Calia/central/toad_in_oak/rooms/ground/path_08.c
 *
 * A path at the ground level of Toad-in-Oak at the southern end of 
 * the village. This room connects to the villages vegie gardens 
 * 
 * HISTORY: [99-03-07] Created by Kcirderf 
 *
 * Copyright (C): Kcirderf 1999
 *
 */

// INCLUSIONS AND DEFINITIONS

inherit "/d/Calia/central/toad_in_oak/rooms/ground/base_ground";

#include <stdproperties.h>
#include "defs.h"

// ROOM DEFINITION

void
create_tio_ground_room()
{

    set_short("A path beneath a village in the trees"); 

    set_long ("You are standing among the massive oaks that fill " +
        "this part of the forest. High above you can see a " + 
        "village nestled among their branches. Any patch of " + 
        "ground here not taken up by trees is instead covered by " + 
        "green grass. To the southeast you can see a large open " + 
        "area which appears to be a vegetable garden.\n"); 

    /*  Exits  */ 

    add_exit(TOAD_IN_OAK_ROOMS_GROUND + "path_09", "northeast"); 
    add_exit(TOAD_IN_OAK_ROOMS_GROUND + "garden_vegetable", "southeast"); 
    add_exit(TOAD_IN_OAK_ROOMS_GROUND + "path_07" , "west"); 

    /*  Items  */ 

    add_item(({"trail", "grass", "path", "ground"}), 
        "A thick carpet of lush green grass covers the ground " + 
        "here. You can make out a faint path through the grass " + 
        "that leads west and northeast as well as southeast into " +
        "the garden.\n"); 

    add_item(({"trees", "tree", "oaks", "oak", "branches"}), 
        "The oaks that make up this part of the forest are truly " + 
        "massive. The village high above you gives you an idea of " + 
        "just how strong their branches are.\n"); 

    add_item(({"village", "walkways"}), 
        "You can see the village among the trees high above you, " + 
        "a number of walkways connecting the trees.\n"); 

    add_item(({"garden", "vegetables"}), 
        "You can see the neat rows of plants that make up the " + 
        "vegetable garden to the southeast, but you can't make " + 
        "out any significant detail from here.\n"); 

}
