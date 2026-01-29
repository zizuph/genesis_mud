#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(16);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r12/f33",
        "southwest" : "r12/f31",
        "south" : "r12/f32",
        "northwest" : "r14/f31",
        "east" : "r13/f33",
        "north" : "r14/f32",
        "northeast" : "r14/f33",
        "west" : "r13/f31",
    ]));
    
}
