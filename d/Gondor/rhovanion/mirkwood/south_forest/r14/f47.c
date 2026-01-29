#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southwest" : "r15/f46",
        "south" : "r15/f47",
        "northwest" : "r13/f46",
        "east" : "r14/f48",
        "north" : "r13/f47",
        "northeast" : "r13/f48",
        "west" : "r14/f46",
    ]));
    
}
