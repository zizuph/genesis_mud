/*
 * /d/Calia/central/toad_in_oak/rooms/ground/path_10.c
 *
 * A path on the ground level of Toad-in-Oak, on the eastern side of the 
 * village itself. This is one of only two places where the stream can be
 * crossed
 *
 * HISTORY: [99-03-11] Created by Kcirderf 
 *
 * Copyright (C): Kcirderf 1999
 *
 */

// INCLUSIONS AND DEFINITIONS

inherit "/d/Calia/central/toad_in_oak/rooms/ground/base_ground";

#include <stdproperties.h>
#include "defs.h"

// ROOM DEFINITION

void create_tio_ground_room()
{

    /*  Description  */ 
    set_short("A path beneath a village in the trees"); 

    set_long("You are standing beneath a village built among the " +
        "branches of the massive oak trees that dominate this " + 
        "part of the forest. Green grass grows all around you " +
        "even though the light here is dim. To the east you can " + 
        "see a large area filled with flowers of many colours.\n");

    /*  Exits  */ 

    add_exit(TOAD_IN_OAK_ROOMS_GROUND + "path_12", "northeast"); 
    add_exit(TOAD_IN_OAK_ROOMS_GROUND + "flowers_north", "east"); 
    add_exit(TOAD_IN_OAK_ROOMS_GROUND + "flowers_west", "southeast"); 
    add_exit(TOAD_IN_OAK_ROOMS_GROUND + "great_oak", "south"); 
    add_exit(TOAD_IN_OAK_ROOMS_GROUND + "path_11", "west"); 

    /*  Items  */ 

    add_item(({"path", "trail", "grass"}), 
        "The grass here seems to be thriving despite the lack of " + 
        "sunlight. You can see several faint trails leading " + 
        "away from here in almost every direction.\n"); 

    add_item(({"trees", "tree", "oaks", "oak", "forest", "branches"}), 
        "@@describe_trees@@"); 

    add_item(({"village", "walkways"}), 
        "You can see a village high above you, or at least the " + 
        "underside of the walkways that connect the trees. You " +
        "can't really make out anything interesting from this " + 
        "angle.\n"); 

    add_item(({"flowers"}), 
        "There are a great number of flowers in the area to the " + 
        "east and southeast of here. The area is filled with " + 
        "colour, and you can see butterflies moving between them " + 
        "occasionally.\n"); 

    return; 
}
       
// FUNCTIONS

/*
 * Function name: describe_trees
 * Description:   Describes the trees that can be seen from this area. 
 *                Theres a little something extra for elves. 
 * Arguments:     none 
 * Returns:       string
 */
string 
describe_trees()
{
    object player = this_player(); 

    string desc; 

    
    
    if (player->query_race_name() == "elf")
    {
        desc = "All of the oaks in this area are very impressive, " +
            "but you find your gaze drawn towards one in particular " + 
            "a ways south of here. You can barely see it from " + 
            "here, but you feel there is something special about " +
            "it.\n"; 
    }
    else
    {
        desc = "The oaks in this area are very impressive, " + 
            "stretching so high above you that they seem to " + 
            "touch the sky. You can see one particular oak to " +
            "the south that is even larger than the others.\n";
    }
            
    return desc; 
}
    
