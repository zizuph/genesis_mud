#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southwest" : "r14/f47",
        "south" : "r14/f48",
        "northwest" : "r12/f47",
        "east" : "r13/f49",
        "north" : "r12/f48",
        "northeast" : "r12/f49",
        "west" : "r13/f47",
    ]));
    
}
