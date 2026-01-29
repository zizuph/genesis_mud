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
    set_room_seed(44);
    set_mirkwood_location(LOCATION_EAST_EDGE);
    set_add_riverrun_near();
    
    ::create_mirkwood_road_room();

    set_add_wildlife();

    set_short("You are on the Old Road somewhere " +
        "near the eastern edge of Mirkwood Forest");

    add_long("The road begins to grow fainter here.",
        ({LIGHT_DUSKDAWN, LIGHT_MIDDAY, LIGHT_BRIGHT}));
    
    add_exit("r45", "east");
    add_exit("r43", "west");

    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r00/f48", "northwest");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r00/f49", "north");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r00/f50", "northeast");
    
    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/f48", "southwest");
    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/f49", "south");
    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/f50", "southeast");
}
