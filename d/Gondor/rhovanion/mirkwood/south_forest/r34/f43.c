#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "northwest" : "r33/f42",
        "east" : "r34/f44",
        "north" : "r33/f43",
        "northeast" : "r33/f44",
        "west" : "r34/f42",
    ]));
    
}
