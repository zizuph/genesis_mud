#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(64);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r13/f16",
        "southwest" : "r13/f14",
        "south" : "r13/f15",
        "northwest" : "r15/f14",
        "east" : "r14/f16",
        "north" : "r15/f15",
        "northeast" : "r15/f16",
        "west" : "r14/f14",
    ]));
    
}
