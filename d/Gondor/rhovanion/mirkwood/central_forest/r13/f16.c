#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(79);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r12/f17",
        "southwest" : "r12/f15",
        "south" : "r12/f16",
        "northwest" : "r14/f15",
        "east" : "r13/f17",
        "north" : "r14/f16",
        "northeast" : "r14/f17",
        "west" : "r13/f15",
    ]));
    
}
