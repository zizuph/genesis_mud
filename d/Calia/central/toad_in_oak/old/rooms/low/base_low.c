/*
 * /d/Calia/central/toad_in_oak/rooms/low/base_low.c
 *
 * This is a baseroom for the low level of Toad-in-Oak
 *
 * HISTORY: [99-07-25] Created by Kcirderf 
 *
 * Copyright (C): Kcirderf 1999
 *
 */

// INCLUSIONS AND DEFINITIONS

inherit "/d/Calia/central/toad_in_oak/rooms/baseroom.c"; 

#include <stdproperties.h>
#include "defs.h"

// ROOM DEFINITION

void
create_tio_low_room()
{
}

public nomask void 
create_tio_room()
{

    add_prop(ROOM_I_LIGHT, 2); 

    create_tio_low_room(); 
}


