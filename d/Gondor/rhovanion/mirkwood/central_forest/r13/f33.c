#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(16);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r12/f34",
        "southwest" : "r12/f32",
        "south" : "r12/f33",
        "northwest" : "r14/f32",
        "east" : "r13/f34",
        "north" : "r14/f33",
        "northeast" : "r14/f34",
        "west" : "r13/f32",
    ]));
    
}
