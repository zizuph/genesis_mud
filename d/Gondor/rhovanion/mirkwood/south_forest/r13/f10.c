#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r14/f11",
        "southwest" : "r14/f09",
        "south" : "r14/f10",
        "northwest" : "r12/f09",
        "east" : "r13/f11",
        "north" : "r12/f10",
        "northeast" : "r12/f11",
        "west" : "r13/f09",
    ]));
    
}
