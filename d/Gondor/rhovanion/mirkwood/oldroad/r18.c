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
    set_room_seed(18);
    set_mirkwood_location(LOCATION_MIDDLE);
    
    ::create_mirkwood_road_room();

    set_add_wildlife();

    set_short("You are on the Old Road somewhere " +
        "in the middle of Mirkwood Forest");

    add_long("An old, dead tree sits along the " +
        "side of the road here. ",
        ({LIGHT_MIDDAY, LIGHT_BRIGHT}));

    add_item_light(({"tree", "dead tree", "old tree", "old dead tree", "bark"}),
        "This is an old, grey tree that obviously died some time back. " +
        "The grey bark of the tree trunk has peeled down and away, curling " +
        "around a small depression in the trunk.\n", ({LIGHT_MIDDAY, LIGHT_BRIGHT}));
    
    add_item_light(({"depression"}),
        "As you look closer, that despression look more black than grey. " +
        "It is apparently a hollowed out hole, rather than a simple " +
        "depression.\n", ({LIGHT_MIDDAY, LIGHT_BRIGHT}));

    add_exit("r19", "east");
    add_exit("r17", "west");

    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r00/f22", "northwest");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r00/f23", "north");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r00/f24", "northeast");
    
    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/f22", "southwest");
    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/f23", "south");
    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/f24", "southeast");

    setuid();
    seteuid(getuid());
    object nest = clone_object(MIRKWOOD_OBJ_DIR + "trunk_hole");
    nest->move(this_object());
}
