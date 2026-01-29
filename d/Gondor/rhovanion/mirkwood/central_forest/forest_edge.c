#include "../defs.h"
#include <stdproperties.h>

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "base";

void create_mirkwood_central_forest_edge_room() {

}

nomask void create_mirkwood_central_forest_room() {
	set_short("You are wandering somewhere " +
    "in the legendary Mirkwood forest");
	// Generic randomized long descriptions
    add_location_long();
    add_tree_long(); 
    add_emo_long(); 
    setup_mirkwood_herbs();
    create_mirkwood_central_forest_edge_room();
}