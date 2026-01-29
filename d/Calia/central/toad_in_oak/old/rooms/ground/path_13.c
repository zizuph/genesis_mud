/*
 * /d/Calia/central/toad_in_oak/rooms/ground/path_13.c
 *
 * A path on the ground level of the village of Toad-In-Oak near the
 * west side of the village, and next to the duck pond
 * 
 * HISTORY: [99-03-19] Created by Kcirderf 
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
    set_short("A path through a great forest"); 

    set_long("You are are standing among the massive oaks that " + 
        "dominate this part of the forest. All around you grows " + 
        "healthy green grass, while a short distance to the north " +
        "there is a dense thicket blocking off the forest in that " + 
        "direction except for a small gap. The area seems " + 
        "unusually peaceful, filled with the pleasant scent of " + 
        "the trees and the distant sounds of tree frogs.\n"); 
    
    /*  Exits  */ 

    add_exit(TOAD_IN_OAK_ROOMS_GROUND + "entrance_north", "north"); 
    add_exit(TOAD_IN_OAK_ROOMS_GROUND + "path_12", "southwest"); 

    /*  Items  */ 

    add_item(({"path", "trail", "debris", "grass", "ground"}), 
        "The grass around here seems to be quite healthy " + 
        "despite the dim light. You can make out a faint path " + 
        "leading to the southwest and the north.\n"); 

    add_item(({"trees", "oaks", "tree", "oak", "forest", "branches", 
        "leaves"}), 
        "The oaks that make up this forest are incredible, " + 
        "reaching so high that they seem to touch the sky. Their " + 
        "upper branches mesh together, nearly blocking out " + 
        "the sunlight at this level.\n"); 

    add_item(({"thicket", "vines", "branches", "vegetation", "thorns"}), 
        "A dense thicket of vines and branches, twisted together " + 
        "and covered in sharp looking thorns forms a nearly " + 
        "impenetrable barrier to the north. Allmost directly north " +
        "of where you stand there is a small gap in the thicket. \n"); 

    return;
}

