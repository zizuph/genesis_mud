
/*
 *  Road running north of Gelan. 
 */ 

#include <stdproperties.h>
#include "defs.h"

inherit (GELAN_ROOMS+"north_road_room"); 

void
create_room()
{
    set_short("Castle road"); 
    make_the_room(0, "north"); 
    add_exit(GELAN_ROOMS+"castle_road_e2", "south"); 
    add_exit(GELAN_ROOMS+"north_road_s2", "north"); 
}
