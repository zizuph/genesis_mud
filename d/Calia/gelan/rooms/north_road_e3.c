
/*
 *  Road running north east of Gelan leading to the Firedrome. 
 */ 

#include <stdproperties.h>
#include "defs.h"
#define FIREDROME_CONNECTION "/d/Calia/fireball/surround/walk2"

inherit (GELAN_ROOMS + "north_road_room"); 


int 
block()
{
/*
    write("Temporarily closed.\n"); 
    return 1; 
*/ 

    return 0; 
}


void
create_room()
{
    set_short("Road to the Firedrome"); 
    make_the_room("Not far to the northeast you see a huge stadium, " +
                  "the Firedrome.", 
                  "northeast"); 
    add_item(({"firedrome", "stadium", "huge stadium"}), 
             "It's a huge stadium of faded red stone. You can " +
             "hear the buzz of a large crowd within.\n"); 
    add_exit(FIREDROME_CONNECTION, "northeast", block); 
    add_exit(GELAN_ROOMS+"north_road_e2", "west"); 
}
