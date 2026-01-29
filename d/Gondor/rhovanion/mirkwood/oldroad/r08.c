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
    set_room_seed(8);
    set_mirkwood_location(LOCATION_WEST_PART);
    
    ::create_mirkwood_road_room();
    
    set_add_wildlife();

    set_short("You are on the Old Road somewhere " +
        "in the western part of Mirkwood Forest");

    add_long("A strange, crooked tree catches your eye on the north " +
        "side of the road. ",
        ({LIGHT_MIDDAY, LIGHT_BRIGHT}));

    add_item_light(({"tree", "crooked tree"}),
        "This tree's trunk and branches are all crooked, yet somehow " +
        "strangely compelling. As you move to inspect the tree a little " +
        "more closely, you notice a small bird's nest nestled in the " +
        "twisted branches.\n", ({LIGHT_MIDDAY, LIGHT_BRIGHT}));

    add_exit("r09", "east");
    add_exit("r07", "west");

    setuid();
    seteuid(getuid());
    object nest = clone_object(MIRKWOOD_OBJ_DIR + "birds_nest");
    nest->move(this_object());

    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r00/f12", "northwest");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r00/f13", "north");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r00/f14", "northeast");
    
    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/f12", "southwest");
    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/f13", "south");
    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/f14", "southeast");
}

