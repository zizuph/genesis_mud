#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r14/f16",
        "southwest" : "r14/f14",
        "south" : "r14/f15",
        "northwest" : "r12/f14",
        "east" : "r13/f16",
        "north" : "r12/f15",
        "northeast" : "r12/f16",
        "west" : "r13/f14",
    ]));
    
}
