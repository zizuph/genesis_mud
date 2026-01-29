/* 
 * /d/Calia/central/toad_in_oak/rooms/ground/trail_04.c
 *
 * Part of the trail up the hill east of TiO, next to the swimming hole
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
    set_short("On the side of a hill in the forest."); 
    set_long("You stand on a thick carpet of grass growing on the side of " + 
        "a hill in the forest of gigantic oak trees. Around the hill to " + 
        "the southwest you can see a large pool of water.\n"); 
    
    add_item(Grass_Words, trail_describe("east", "west")); 
    add_item(Hill_Words, hill_describe()); 
    add_item(Tree_Words, trees_describe(0, "")); 
    add_item(Swim_Words, "@@swim_describe@@"); 

    add_tell("You hear the sound of falling water somewhere nearby.\n"); 

    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "trail_05", "east"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "swim_shore", "southeast"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "trail_03", "west"); 
}
