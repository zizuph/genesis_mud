#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r14/f40",
        "southwest" : "r14/f38",
        "south" : "r14/f39",
        "northwest" : "r12/f38",
        "east" : "r13/f40",
        "north" : "r12/f39",
        "northeast" : "r12/f40",
        "west" : "r13/f38",
    ]));
    
}
