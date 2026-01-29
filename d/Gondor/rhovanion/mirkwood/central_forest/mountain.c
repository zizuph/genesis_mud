#include "../defs.h"
#include <stdproperties.h>

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "base";

void create_mirkwood_central_forest_mountain_room() {

}

nomask void create_mirkwood_central_forest_room() {
	set_short("You are wandering somewhere in the mountains " +
    "of the legendary Mirkwood forest");
    // Generic randomized long descriptions
    add_mountain_long();
    add_mountain2_long(); 
    add_mountain3_long(); 
    setup_mirkwood_herbs();
    create_mirkwood_central_forest_mountain_room();
}

void set_distance_to_edge(int distance) {
    switch(distance) {
        case 0: set_movement_difficulty(70 + random(10)); break;
        case 1: set_movement_difficulty(70 + random(20)); break;
        case 2: set_movement_difficulty(80 + random(15)); break;
        case 3: set_movement_difficulty(80 + random(20)); break;
        case 4: set_movement_difficulty(90 + random(10)); break;
        default: set_movement_difficulty(100); break;
    }
}