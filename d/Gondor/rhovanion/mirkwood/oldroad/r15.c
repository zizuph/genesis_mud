/*
 * Room of the Old Road in Mirkwood.
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
    set_room_seed(15);
    set_mirkwood_location(LOCATION_MIDDLE);
    
    ::create_mirkwood_road_room();

    set_add_wildlife();

    set_short("You are on the Old Road somewhere " +
        "in the middle of Mirkwood Forest");
    
    add_exit("r16", "east");
    add_exit("r14", "west");

    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r00/f19", "northwest");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r00/f20", "north");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r00/f21", "northeast");
    
    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/f19", "southwest");
    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/f20", "south");
    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/f21", "southeast");
}
