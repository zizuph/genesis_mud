#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(25);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r14/f16",
        "southwest" : "r14/f14",
        "south" : "r14/f15",
        "northwest" : "r16/f14",
        "east" : "r15/f16",
        "north" : "r16/f15",
        "northeast" : "r16/f16",
        "west" : "r15/f14",
    ]));
    
}
