#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r14/f43",
        "southwest" : "r14/f41",
        "south" : "r14/f42",
        "northwest" : "r12/f41",
        "east" : "r13/f43",
        "north" : "r12/f42",
        "northeast" : "r12/f43",
        "west" : "r13/f41",
    ]));
    
}
