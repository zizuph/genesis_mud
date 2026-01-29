#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r14/f44",
        "southwest" : "r14/f42",
        "south" : "r14/f43",
        "northwest" : "r12/f42",
        "east" : "r13/f44",
        "north" : "r12/f43",
        "northeast" : "r12/f44",
        "west" : "r13/f42",
    ]));
    
}
