#include "../defs.h"
#include <stdproperties.h>

inherit MIRKWOOD_SOUTH_FOREST_DIR + "base";

void create_mirkwood_south_forest_path_room() {

}

nomask void create_mirkwood_south_forest_room() {
	set_short("You are following a path somewhere " +
		"south of the old road in Mirkwood forest");
    // Generic randomized long descriptions
    add_path1();
    add_path2(); 
    add_path3(); 
    setup_mirkwood_herbs();
    create_mirkwood_south_forest_path_room();
}