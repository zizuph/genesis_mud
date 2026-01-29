
/*
 *  Road running north east of Gelan leading to the Firedrome. 
 */ 

#include <stdproperties.h>
#include "defs.h"

inherit (GELAN_ROOMS+"north_road_room"); 


void
create_room()
{
    set_short("Road to the Firedrome"); 
    make_the_room("A long way to the east you see a huge stadium, " +
                  "the Firedrome.", "northeast"); 
    add_item(({"firedrome", "stadium", "huge stadium"}), 
             "It's a huge circular stadium of faded red stone.\n"); 
    add_exit(GELAN_ROOMS+"north_road_e2", "northeast"); 
    add_exit(GELAN_ROOMS+"north_road_e0", "west"); 
}
