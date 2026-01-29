#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(36);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r12/f16",
        "southwest" : "r12/f14",
        "south" : "r12/f15",
        "northwest" : "r14/f14",
        "east" : "r13/f16",
        "north" : "r14/f15",
        "northeast" : "r14/f15",
        "west" : "r13/f14",
    ]));
    
}
