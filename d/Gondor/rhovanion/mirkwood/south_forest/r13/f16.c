#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(10);
    add_mirkwood_exits(([
        "southeast" : "r14/f17",
        "southwest" : "r14/f15",
        "south" : "r14/f16",
        "northwest" : "r12/f15",
        "east" : "r13/f17",
        "north" : "r12/f16",
        "northeast" : "r12/f17",
        "west" : "r13/f15",
    ]));
    
}
