#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r14/f41",
        "southwest" : "r14/f39",
        "south" : "r14/f40",
        "northwest" : "r12/f39",
        "east" : "r13/f41",
        "north" : "r12/f40",
        "northeast" : "r12/f41",
        "west" : "r13/f39",
    ]));
    
}
