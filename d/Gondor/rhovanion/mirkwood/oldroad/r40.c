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
    set_room_seed(40);
    set_mirkwood_location(LOCATION_EAST_PART);
    
    ::create_mirkwood_road_room();

    set_add_wildlife();

    set_short("You are on the Old Road somewhere " +
        "in the eastern part of Mirkwood Forest");
    
    add_exit("r41", "east");
    add_exit("r39", "west");

    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r00/f44", "northwest");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r00/f45", "north");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r00/f46", "northeast");
    
    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/f44", "southwest");
    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/f45", "south");
    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/f46", "southeast");
}
