#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southwest" : "r16/f46",
        "northwest" : "r14/f46",
        "north" : "r14/f47",
        "northeast" : "r14/f48",
        "west" : "r15/f46",
    ]));
    
}
