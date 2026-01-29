#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r15/f16",
        "southwest" : "r15/f14",
        "south" : "r15/f15",
        "northwest" : "r13/f14",
        "east" : "r14/f16",
        "north" : "r13/f15",
        "northeast" : "r13/f16",
        "west" : "r14/f14",
    ]));
    
}
