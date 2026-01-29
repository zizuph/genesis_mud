/*
 * Room of the Old Road in Mirkwood.
 * Varian - Nov, 2012
 *
 */

#include "../defs.h"
#include <stdproperties.h>

inherit MIRKWOOD_OLDROAD_DIR + "base";

/*
 * Function name: create_mirkwood_road_room
 * Description  : Create this room of the old road
 */
void create_mirkwood_road_room()
{
    // Force the randomized messages to always be the same for roads
    set_room_seed(2);
    set_mirkwood_location(LOCATION_WEST_EDGE);
        
    ::create_mirkwood_road_room();

    set_add_wildlife();

    set_short("You are on the Old Road somewhere " +
        "near the western edge of Mirkwood Forest");
    
    

   add_exit("r03", "east");
   add_exit("r01", "west");

    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r00/f07", "north");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r00/f08", "northeast");

    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/f06", "southwest");
    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/f07", "south");
    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/f08", "southeast");
}
