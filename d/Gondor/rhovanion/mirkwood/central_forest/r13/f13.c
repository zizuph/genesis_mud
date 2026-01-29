#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(22);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r12/f14",
        "southwest" : "r12/f12",
        "south" : "r12/f13",
        "northwest" : "r14/f12",
        "east" : "r13/f14",
        "north" : "r14/f13",
        "northeast" : "r14/f14",
        "west" : "r13/f12",
    ]));
    
}
