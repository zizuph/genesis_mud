#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(11);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r14/f15",
        "southwest" : "r14/f13",
        "south" : "r14/f14",
        "northwest" : "r16/f13",
        "east" : "r15/f15",
        "north" : "r16/f14",
        "northeast" : "r16/f15",
        "west" : "r15/f13",
    ]));
    
}
