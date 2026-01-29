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
    set_room_seed(46);
    set_mirkwood_location(LOCATION_EAST_EDGE);
    set_add_riverrun_close();
    
    ::create_mirkwood_road_room();

    set_add_wildlife();

    set_short("You are on the Old Road somewhere " +
        "on the eastern edge of Mirkwood Forest");

    add_long("To the east, the road seems to vanish into a swamp.",
        ({LIGHT_DUSKDAWN, LIGHT_MIDDAY, LIGHT_BRIGHT}));

    add_item_light(({"swamp", "murky swamp"}),
        "You cannot see much from here, as you are still in the forest, but " +
        "just ahead of you, to the east, the road seems to descend into what " +
        "appears to be a large " +
        "swamp.\n", ({LIGHT_DUSKDAWN, LIGHT_MIDDAY, LIGHT_BRIGHT}));
    
    add_exit("r45", "west");
    add_exit("r45", "east", "@@swamp@@", 1,1);
    add_exit("r45", "northeast", "@@swamp2@@", 1,1);
    add_exit("r45", "southeast", "@@swamp2@@", 1,1);

    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r00/f50", "northwest");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r00/f51", "north");

    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/f50", "southwest");
    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/f51", "south");
}
int
swamp()
{
write("As you try to move further east, you notice that the road " +
    "seems to disappear into a murky swamp. It is impossible to " +
    "continue in that direction.\n");
return 1;
}

int
swamp2()
{
write("The ground starts to give way under your feet as you attempt " +
    "to wander into the middle of a swamp. You make your way back " +
    "to the old road where the ground is more secure.\n");
return 1;
}