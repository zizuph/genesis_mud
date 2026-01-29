#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r14/f48",
        "southwest" : "r14/f46",
        "south" : "r14/f47",
        "northwest" : "r12/f46",
        "east" : "r13/f48",
        "north" : "r12/f47",
        "northeast" : "r12/f48",
        "west" : "r13/f46",
    ]));
    
}
