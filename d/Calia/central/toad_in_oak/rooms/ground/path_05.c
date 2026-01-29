/* 
 * /d/Calia/central/toad_in_oak/rooms/ground/path_05.c
 *
 * A path in the north of TiO, near the flower garden
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
    set_short("A path beneath a vilage in the trees."); 
    set_long("You stand on the lush green grass that covers the ground " + 
        "here, filling the spaces between the trunks of the enormous " + 
        "oak trees that dominate this forest. Off to the east the grass " + 
        "begins to give way to a multitude of colourful flowers, while " + 
        "a faint path curves around the trunk of a particularly large " + 
        "oak that dwarfs the others to the south. There appears to be " + 
        "a village built in the branches of the trees far above.\n"); 
   
    add_item(({"flowers"}), 
        "To the east and southeast of where you are standing you can see " +
        "large patches of flowers of many different types growing. From " +
        "here any details are lost in the sea of bright colours.\n"); 
    
    add_item(({"large oak", "large tree"}), 
        "Calling this oak 'large' is a gross understatement. Though it is " +
        "a good distance away you can tell from here that it is quite " + 
        "significantly larger than the other trees of the forest, which " + 
        "are enormous in their own right.\n"); 

    add_item(Grass_Words, 
        grass_describe(({"northeast", "east", "southeast", "south", "west"}))); 
    add_item(Tree_Words, trees_describe(1, "south")); 
    add_item(Village_Words, village_describe()); 

    add_tell("A butterfly flutters by, heading towards the flowers east " + 
        "of here.\n"); 
    add_tell("A bee buzzes past your ear on it's way home after a visit " +
        "to the flowers.\n"); 


    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "path_06", "northeast"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "flowers_n", "east"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "flowers_w", "southeast"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "great_oak", "south"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "path_04", "west"); 
}

void
hook_smelled(string smelled)
{
    if (smelled == "flowers") 
    {
        write("You can detect a floral scent in the air from here, " + 
            "but you are too far away to really smell the flowers.\n"); 
    }
    else
    {
        common_smells(smelled); 
    }
}


