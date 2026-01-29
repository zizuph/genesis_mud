#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r14/f34",
        "southwest" : "r14/f32",
        "south" : "r14/f33",
        "northwest" : "r12/f32",
        "east" : "r13/f34",
        "north" : "r12/f33",
        "northeast" : "r12/f34",
        "west" : "r13/f32",
    ]));
    
}
