
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
    make_the_room(0, "northeast"); 
    add_exit(GELAN_ROOMS+"north_road_e1", "east"); 
    add_exit(GELAN_ROOMS+"north_road_s3", "west"); 
}
