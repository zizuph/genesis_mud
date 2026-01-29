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
    set_room_seed(36);
    set_mirkwood_location(LOCATION_MIDDLE);
    
    ::create_mirkwood_road_room();

    set_add_wildlife();

    set_short("You are on the Old Road somewhere " +
        "in the middle of Mirkwood Forest");

    add_long("A small path curves away from the old road, winding its " +
        "way southeast through the trees.",
        ({ LIGHT_MIDDAY, LIGHT_BRIGHT }));

    add_item_light(({"path","well-worn path","south trees"}),
        "This path curves away from the old road, winding its way through " +
        "the trees southeast, deeper into Mirkwood " +
        "forest.\n", ({ LIGHT_MIDDAY, LIGHT_BRIGHT }));
    
    add_exit("r37", "east");
    add_exit("r35", "west");

    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r00/f40", "northwest");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r00/f41", "north");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r00/f42", "northeast");
    
    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/f40", "southwest");
    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/f41", "south");
    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/p42", "southeast");
}
