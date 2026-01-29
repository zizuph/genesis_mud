#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(15);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r12/f36",
        "southwest" : "r12/f34",
        "south" : "r12/f35",
        "northwest" : "r14/f34",
        "east" : "r13/f36",
        "north" : "r14/f35",
        "northeast" : "r14/f36",
        "west" : "r13/f34",
    ]));
    
}
