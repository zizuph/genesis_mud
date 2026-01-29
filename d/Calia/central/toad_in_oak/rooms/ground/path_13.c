/* 
 * /d/Calia/central/toad_in_oak/rooms/ground/path_13.c
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

    set_short("A path beneath a village in the trees."); 
    set_long("All around you the trunks of massive oak trees stetch " + 
        "skyward, a village nestled in their branches high above. The " + 
        "ground not taken up by the huge trees is covered in springy " + 
        "green grass.\n"); 

    add_item(Grass_Words, grass_describe(({"east", "southwest"}))); 
    add_item(Tree_Words, trees_describe(1, "north"));
    add_item(Village_Words, village_describe());     
   
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "path_14", "east"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "path_12", "southwest"); 
}
