/*
 * /d/Calia/central/toad_in_oak/rooms/ground/path_12.c
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

    set_long("You are standing among the stately oaks that make " + 
        "up this part of the forest. Healthy green grass covers " + 
        "the ground between the trees. A little ways to the south " +
        "you can see a small village nestled amongst the branches " + 
        "of the trees.\n"); 
    
    /*  Exits  */ 

    add_exit(TOAD_IN_OAK_ROOMS_GROUND + "path_13", "northeast"); 
    add_exit(TOAD_IN_OAK_ROOMS_GROUND + "path_10", "southwest"); 

    /*  Items  */ 

    add_item(({"path", "trail", "debris", "grass"}), 
        "The carpet of green grass grows well despite the dim " + 
        "light at this level, filling in all the space between " + 
        "the trees. A faint path runs through the grass, leading " +
        "towards the northeast and the southwest.\n"); 

    add_item(({"trees", "oaks", "tree", "oak", "trunks", "branches", 
        "forest", "leaves"}), 
        "The trees here are awe-inspiring, their straight trunks " + 
        "stretching hundreds of feet above you. Their upper " + 
        "branches and leaves cover the sky like a roof, leaving " + 
        "the ground covered in shadows.\n"); 

    add_item(({"village", "walkways"}), 
        "You can see a number of walkways high above the ground " + 
        "connecting the trees a little ways to the south of here.\n"); 

    return;
}

