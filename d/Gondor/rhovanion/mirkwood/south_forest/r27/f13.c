#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "northwest" : "r26/f12",
        "east" : "r27/f14",
        "north" : "r26/f13",
        "northeast" : "r26/f14",
    ]));
    
}
