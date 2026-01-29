#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(78);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r12/f18",
        "southwest" : "r12/f16",
        "south" : "r12/f17",
        "northwest" : "r14/f16",
        "east" : "r13/f18",
        "north" : "r14/f17",
        "northeast" : "r14/f18",
        "west" : "r13/f16",
    ]));
    
}
