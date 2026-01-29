#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r14/f33",
        "southwest" : "r14/f31",
        "south" : "r14/f32",
        "northwest" : "r12/f31",
        "east" : "r13/f33",
        "north" : "r12/f32",
        "northeast" : "r12/f33",
        "west" : "r13/f31",
    ]));
    
}
