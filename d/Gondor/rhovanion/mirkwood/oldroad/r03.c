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
    set_room_seed(3);
    set_mirkwood_location(LOCATION_WEST_EDGE);
    
    ::create_mirkwood_road_room();

	set_add_wildlife();

    set_short("You are on the Old Road somewhere " +
        "near the western edge of Mirkwood Forest");

    add_long("Almost hidden behind the trees on the south side of the " +
    	"road, you see a strange looking tree stump. ", ({ LIGHT_MIDDAY, LIGHT_BRIGHT }));

    add_item_light(({"stump", "tree stump", "bear", "carving", "image"}), 
    	"This tree stump seems to " +
    	"have been carefully carved to appear in the shape of a " +
    	"bear. There are no other markings or clues as to why " +
    	"this carving was made here, or even who carved it.\n", ({ LIGHT_MIDDAY, LIGHT_BRIGHT }));

    add_exit("r04", "east");
    add_exit("r02", "west");

    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r00/f07", "northwest");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r00/f08", "north");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r00/f09", "northeast");

    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/f07", "southwest");
    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/f08", "south");
    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/p09-r00", "southeast");

    setuid();
    seteuid(getuid());
    object shelter = clone_object(MIRKWOOD_OBJ_DIR + "shelter");
    shelter->move(this_object());
}

int press_cmd(string args) {
    int light_level = query_light_level_for_living(this_player());

    if (!args || !strlen(args) || (light_level != LIGHT_BRIGHT)) {
        notify_fail("What?\n");
        return 0;
    }

        if (parse_command(args, ({}), "'carving' / 'image' / 'bear' [image] / [images] / [carving] / [carvings]")) {
        write("You press down firmly on the bear image and wait a few "
              + "moments, but nothing seems to happen.\n");
        return 1;    
    }

    
    notify_fail("Perhaps you wanted to press on " +
        "the bear carving instead?\n");
    return 0;
}

void init() {
    ::init();
    add_action(press_cmd, "press");
}


