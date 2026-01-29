#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(67);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r13/f17",
        "southwest" : "r13/f15",
        "south" : "r13/f16",
        "northwest" : "r15/f15",
        "east" : "r14/f17",
        "north" : "r15/f16",
        "northeast" : "r15/f17",
        "west" : "r14/f15",
    ]));
    
}
