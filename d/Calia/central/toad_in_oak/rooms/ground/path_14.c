/* 
 * /d/Calia/central/toad_in_oak/rooms/ground/path_14.c
 *
 * A path on the southern edge of TiO
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
    set_short("A path beneath a village in the trees.\n"); 
    set_long("You stand directly beneath a walkway of a village built " + 
        "into the branches of the titanic oak trees that souround you. " + 
        "A thick layer of grass covers the ground between the trunks of " + 
        "the trees.\n"); 
    
    add_item(Grass_Words, grass_describe(({"northeast", "west"}))); 
    add_item(Tree_Words, trees_describe(1, "northwest")); 
    add_item(Village_Words, village_describe()); 

    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "path_15", "northeast"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "path_13", "west"); 
}
