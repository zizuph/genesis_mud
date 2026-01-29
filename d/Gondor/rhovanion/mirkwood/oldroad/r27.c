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
    set_room_seed(27);
    set_mirkwood_location(LOCATION_MIDDLE);
    
    ::create_mirkwood_road_room();

    set_add_wildlife();

    set_short("You are on the Old Road somewhere " +
        "in the middle of Mirkwood Forest");
    
    add_exit("r28", "east");
    add_exit("r26", "west");

    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r00/f31", "northwest");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r00/f32", "north");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r00/f33", "northeast");
    
    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/f31", "southwest");
    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/f32", "south");
    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/f33", "southeast");
}
