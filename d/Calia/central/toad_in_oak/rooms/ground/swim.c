/* 
 * /d/Calia/central/toad_in_oak/rooms/ground/swim.c
 *
 * This is the swimming hole on the hill east of TiO. 
 * This may need some serious coding and could be expanded to be
 * more than one room. 
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
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "swim_shore", "exit"); 
}
