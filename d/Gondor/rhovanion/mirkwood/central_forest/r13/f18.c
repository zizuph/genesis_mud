#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(90);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r12/f19",
        "southwest" : "r12/f17",
        "south" : "r12/f18",
        "northwest" : "r14/f17",
        "east" : "r13/f19",
        "north" : "r14/f18",
        "northeast" : "r14/f19",
        "west" : "r13/f17",
    ]));
    
}
