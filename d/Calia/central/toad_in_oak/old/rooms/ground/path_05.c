/*
 * /d/Calia/central/toad_in_oak/ground/rooms/path_05.c
 *
 * A path at the ground level of Toad-in-Oak at the southern end of 
 * the village
 * 
 * HISTORY: [99-03-04] Created by Kcirderf 
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
    
    set_long("You stand among the monumental oak trees that make " + 
        "up this part of the forest, a small village supported by " + 
        "strong limbs high above. Green grass covers " +
        "the ground, stopping only for the massive tree trunks " + 
        "and the edge of the dense thicket to the south. The " +
        "scents and soft sounds of the forest give the area a " +
        "feeling of peace.\n"); 

    /*  exits  */ 

    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "green_se", "northwest"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "path_06" , "east"); 

    /*  Items  */ 

    add_item(({"trees", "oaks", "tree", "oak", "forest", "trunks", "limbs"}),
        "The leaves of these massive oaks nearly block out the " + 
        "sun high above you, leaving you just enough light to " + 
        "avoid walking into the huge trunks.\n"); 

    add_item(({"path", "trail", "grass"}), 
        "The grass here is green and healthy despite the dim " + 
        "lighting. It grows over every patch of ground that's not " +
        "already occupied by the oaks or the thicket. You can see " + 
        "a faint path heading towards the northwest and the east.\n"); 

    add_item(({"vegetation", "thicket", "branches", "vines", "thorns"}),     
        "A dense tangled mass of branches and vines full of sharp " + 
        "thorns forms an impassible barrier to the south of the " + 
        "path.\n"); 

    add_item(({"village", "walkways"}), 
        "You can see the underside of the walkways that connect " + 
        "the village far above you. You can see people walking " + 
        "by occasionally, but you can't make out any significant " + 
        "detail from down here.\n"); 

}
