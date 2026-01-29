#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "northwest" : "r39/f14",
        "east" : "r40/f16",
        "north" : "r39/f15",
        "northeast" : "r39/f16",
        "west" : "r40/f14",
    ]));
    
}
