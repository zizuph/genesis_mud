#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(35);

    set_distance_to_edge(6);
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
