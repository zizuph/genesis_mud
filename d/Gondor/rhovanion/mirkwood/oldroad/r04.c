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
    set_room_seed(4);
    set_mirkwood_location(LOCATION_WEST_PART);
    
    ::create_mirkwood_road_room();

    set_add_wildlife();

    set_short("You are on the Old Road somewhere " +
        "in the western part of Mirkwood Forest");
    
    add_long("A small path twists through the trees on the south " +
        "side of the road, barely visible even in this light. ",
        ({ LIGHT_MIDDAY, LIGHT_BRIGHT }));

    add_item_light(({"path","small path","south trees"}),
        "This small path seems to be well used, yet it is so " +
        "well concealed that you are certain it is for " +
        "private use only.\n", ({ LIGHT_MIDDAY, LIGHT_BRIGHT }));
    
    add_exit("r05", "east");
    add_exit("r03", "west");

    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r00/f08", "northwest");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r00/f09", "north");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r00/f10", "northeast");
    
    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/f08", "southwest");
    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/p09-r00", "south");
    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/f10", "southeast");
}
