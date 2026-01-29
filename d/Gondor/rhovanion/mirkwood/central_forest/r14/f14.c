#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(32);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r13/f15",
        "southwest" : "r13/f13",
        "south" : "r13/f14",
        "northwest" : "r15/f13",
        "east" : "r14/f15",
        "north" : "r15/f14",
        "northeast" : "r15/f15",
        "west" : "r14/f13",
    ]));
    
}
