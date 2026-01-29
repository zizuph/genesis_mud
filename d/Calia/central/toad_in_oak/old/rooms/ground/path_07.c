/*
 * /d/Calia/central/toad_in_oak/rooms/ground/path_07.c 
 *
 * A path at the ground level of Toad-in-Oak at the southern end of 
 * the village. This room connects to the villages mushroom gardens
 * 
 * HISTORY: [99-03-05] Created by Kcirderf 
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

    set_short("A path in beneath a village in the trees"); 

    set_long("You stand among the stately oaks that make up this " + 
        "part of the forest. Far above you in the branches of the " + 
        "trees you can see the underside of a small village. Lush " + 
        "green grass covers every patch of the ground here that " + 
        "is not already taken up by the trees.\n"); 

    /* exits  */

    add_exit(TOAD_IN_OAK_ROOMS_GROUND + "path_06", "southwest"); 
    add_exit(TOAD_IN_OAK_ROOMS_GROUND + "path_08", "east"); 

    /*  Items  */ 

    add_item(({"path", "trail", "grass"}),
        "The grass here is green and healthy despite the shade " + 
        "that covers the ground. You can make out a faint path " + 
        "through the grass that leads to the southwest and the " + 
        "east.\n"); 

    add_item(({"trees", "tree", "oaks", "oak", "forest", "trunk"}), 
        "The trees here are truly spectacular, towering high " + 
        "above the ground. If hollow, their trunks could easily " + 
        "hold a dozen people, and they soar into the sky far " + 
        "above. Their uppermost leaves form a green ceiling over " + 
        "the area and cover the ground with shade.\n"); 

    add_item(({"village", "walkways"}), 
        "High above you can see wide walkways running between the " +
        "various trees. They doesn't appear to be very active, but " +
        "then again you can only see the underside of it.\n"); 

}


