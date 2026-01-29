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
    set_room_seed(30);
    set_mirkwood_location(LOCATION_MIDDLE);
    
    ::create_mirkwood_road_room();

    set_add_wildlife();

    set_short("You are on the Old Road somewhere " +
        "in the middle of Mirkwood Forest");

    add_long("Along the south side of the road, you see an old, " +
    	"fallen log. ", ({ LIGHT_MIDDAY, LIGHT_BRIGHT }));

    add_item_light(({"log", "old log", "fallen log", "old fallen log"}), 
    	"Laying by the south side of the road, is the remains of a once massive " +
    	"tree. The rough, black bark on the outside still appears to be firm, " +
    	"yet the inside appears to be hollow.\n", ({ LIGHT_MIDDAY, LIGHT_BRIGHT }));
    add_item_light(({"hollow log", "hollow", "inside"}), 
    	"You lean over and look more closely at the log. Yes, it does " +
    	"appear to be hollow. It also appears to be very dark, and by " +
    	"the smell of it, perhaps even the home of some sort of " +
    	"small animal.\n", ({ LIGHT_MIDDAY, LIGHT_BRIGHT }));
    add_item_light(({"bark", "black bark", "rough bark", "rough black bark"}), 
    	"As you look closely at the bark on this log, you can see that it has " +
    	"peeled off in some places. However, it is intact for the most part " +
    	"as it seems to have dried out along with the remaining wooden " +
    	"shell.\n", ({ LIGHT_MIDDAY, LIGHT_BRIGHT }));
    add_item_light(({"animal", "small animal"}), 
    	"You look around carefully, but you cannot see any small animals here." +
    	"However, you strongly suspect that if there are not small animals " +
    	"currently living inside this log, there must have been some that did " +
    	"live here recently.\n", ({ LIGHT_MIDDAY, LIGHT_BRIGHT }));
    add_item_light(({"shell", "wooden shell"}), 
    	"You lean forward and climb across the log to get a better look " +
    	"at where some of the bark has peeled away. For the most part, it " +
    	"looks like a regular wooden log, but there are a reddish-brown marks " +
    	"that sort of look like handprints.\n", ({ LIGHT_MIDDAY, LIGHT_BRIGHT }));
    add_item_light(({"hand", "handprint", "mark", "brown mark", "reddish-brown mark", "blood"}), 
    	"Well, it sort of looks like a hand when you see it from this  " +
    	"direction. It is possible that someone could have had some blood " +
    	"on their hands and left a handprint behind. If so, it was a long " +
    	"time ago and they are not here any longer.\n", ({ LIGHT_MIDDAY, LIGHT_BRIGHT }));

    
    add_exit("r31", "east");
    add_exit("r29", "west");

    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r00/f34", "northwest");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r00/f35", "north");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r00/f36", "northeast");
    
    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/f34", "southwest");
    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/f35", "south");
    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/f36", "southeast");
}
