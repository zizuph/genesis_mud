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
    set_room_seed(45);
    set_mirkwood_location(LOCATION_EAST_EDGE);
    set_add_riverrun_close();
    
    ::create_mirkwood_road_room();

    set_add_wildlife();

    set_short("You are on the Old Road somewhere " +
        "near the eastern edge of Mirkwood Forest");

    add_long("The road begins to grow fainter here.",
        ({LIGHT_DUSKDAWN, LIGHT_MIDDAY, LIGHT_BRIGHT}));
    
    add_exit("r46", "east");
    add_exit("r44", "west");

    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r00/f49", "northwest");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r00/f50", "north");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r00/f51", "northeast");
    
    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/f49", "southwest");
    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/f50", "south");
    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/f51", "southeast");
}
