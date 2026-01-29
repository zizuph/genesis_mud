
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
    make_the_room("A fair way to the east you see a huge stadium, " +
                  "the Firedrome.", "northeast"); 
    add_item(({"stadium", "huge stadium", "firedrome"}), 
             "It's a huge circular stadium of faded red " +
             "stone. You can just hear the noise of a distant " +
             "crowd from that direction.\n"); 

    add_exit(GELAN_ROOMS+"north_road_e3", "east"); 
    add_exit(GELAN_ROOMS+"north_road_e1", "southwest"); 
}
