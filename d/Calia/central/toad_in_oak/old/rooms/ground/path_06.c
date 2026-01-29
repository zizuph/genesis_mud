/*
 * /d/Calia/central/toad_in_oak/ground/rooms/path_07.c
 *
 * A path at the ground level of Toad-in-Oak at the southern end of 
 * the village. This one is not at the edge of the village, so the 
 * "wall" is not visible. 
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

    set_long("You are standing on the carpet of grass that grows " + 
        "among the trunks of the awe inpspiring oaks that " + 
        "dominate the area. High above in the branches of the " + 
        "trees you can see the underside of a small village. " + 
        "There is little light at this level, but the pleasant " + 
        "sounds and smells of the forest make the place seem " +
        "bright and cheerful. To the south of the path grows an " + 
        "impassible thicket of dense vegetation.\n"); 

    /*  Exits  */ 

    add_exit(TOAD_IN_OAK_ROOMS_GROUND + "path_07" , "northeast"); 
    add_exit(TOAD_IN_OAK_ROOMS_GROUND + "garden_mushroom" , "east" ); 
    add_exit(TOAD_IN_OAK_ROOMS_GROUND + "path_05" , "west" ); 
    add_exit( TOAD_IN_OAK_ROOMS_LOW + "walkway_10", "up");

    /*  Items  */ 
    add_item(({"path", "trail", "grass"}), 
        "The grass here is thick and green and healthy, as if it " + 
        "were growing in open sunlight. You can barely pick out a " + 
        "faint trail through the grass coming from the west that " + 
        "forks to the northeast and to the east.\n"); 

    add_item(({"trees", "tree", "oaks", "oak", "forest", "trunks"}), 
        "These oaks are amazing, their trunks so wide that it " + 
        "would take several people to encircle them. They stretch " +
        "high into the sky, their leafy upper branches forming " + 
        "a green roof over the forest.\n"); 
    
    add_item(({"thicket", "vegetation", "branches", "vines", 
        "thorns", "wall"}), 
        "A dense thicket of thorny shrubs, gnarled branches, and " +
        "entangled vines lies south of here, preventing you from " + 
        "going farther south into the forest.\n"); 

    add_item(({"village", "walkways"}), 
        "High above you you can see the underside of the village's " +
        "walkways. It's impossible to make out any details from " + 
        "down here.\n"); 

}
