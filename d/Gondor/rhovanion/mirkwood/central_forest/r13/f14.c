#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(51);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r12/f15",
        "southwest" : "r12/f13",
        "south" : "r12/f14",
        "northwest" : "r14/f13",
        "east" : "r13/f15",
        "north" : "r14/f14",
        "northeast" : "r14/f15",
        "west" : "r13/f13",
    ]));
    
}
