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
    set_room_seed(5);
    set_mirkwood_location(LOCATION_WEST_PART);
    
    ::create_mirkwood_road_room();

    set_add_wildlife();

    set_short("You are on the Old Road somewhere " +
        "in the western part of Mirkwood Forest");
    
    add_long("Tucked away behind some of the underbrush, you can " +
    	"see a strange looking rock. ", ({ LIGHT_MIDDAY, LIGHT_BRIGHT }));

    add_item_light(({"rock", "boulder", "bear", "carving"}), 
    	"As you look closer, you notice that a small boulder " +
    	"was chiseled and shaped to create several images " +
    	"of bears, including a ferocious looking bear's face " +
    	"in mid-roar.\n", ({ LIGHT_MIDDAY, LIGHT_BRIGHT }));
    add_item_light(({"face", "bear face"}), 
    	"You examine the snarling face closer, even reaching " +
    	"out with your fingers to touch the realistic " +
    	"looking fangs.\n", ({ LIGHT_MIDDAY, LIGHT_BRIGHT }));
    add_item_light(({"fangs", "fang", "snout"}), 
    	"This is obviously the work of a very talented sculptor, " +
    	"as these fangs seem to lunge out of the boulder along with " +
    	"the rest of the bear's snout in a very realistic fashion. " +
    	"The more you look, the more you wonder if someone, " +
    	"somehow, trapped a real bear inside this rock. \n", ({ LIGHT_MIDDAY, LIGHT_BRIGHT }));

    add_exit("r06", "east");
    add_exit("r04", "west");

    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r00/f09", "northwest");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r00/f10", "north");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r00/f11", "northeast");
    
    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/p09-r00", "southwest");
    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/f10", "south");
    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/f11", "southeast");
}
