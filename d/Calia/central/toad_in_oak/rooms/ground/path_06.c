/* 
 * /d/Calia/central/toad_in_oak/rooms/ground/path_06.c
 *
 * A path on the northern edge of TiO
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
    set_short("A path beaneath a village in the trees."); 
    set_long("You stand amid the enormous oak trees that make up this " + 
        "part of the forest, their branches so high that they seem to " +
        "touch the sky. Thick green grass covers the ground between " + 
        "their trunks, covered in the shifting shadows of their leaves. " +
        "You can see the underside of a village built in the branches " + 
        "of the trees above you.\n"); 

    add_item(Grass_Words, grass_describe(({"northeast", "southwest"}))); 
    add_item(Tree_Words, trees_describe(1, "")); 
    add_item(Village_Words, village_describe()); 

    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "path_07", "northeast"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "path_05", "southwest"); 
}
