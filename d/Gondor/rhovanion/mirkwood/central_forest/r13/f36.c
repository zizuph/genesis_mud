#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(11);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r12/f37",
        "southwest" : "r12/f35",
        "south" : "r12/f36",
        "northwest" : "r14/f35",
        "east" : "r13/f37",
        "north" : "r14/f36",
        "northeast" : "r14/f37",
        "west" : "r13/f35",
    ]));
    
}
