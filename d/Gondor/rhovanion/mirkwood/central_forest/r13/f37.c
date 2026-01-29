#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(18);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r12/f38",
        "southwest" : "r12/f36",
        "south" : "r12/f37",
        "northwest" : "r14/f36",
        "east" : "r13/f38",
        "north" : "r14/f37",
        "northeast" : "r14/f38",
        "west" : "r13/f36",
    ]));
    
}
