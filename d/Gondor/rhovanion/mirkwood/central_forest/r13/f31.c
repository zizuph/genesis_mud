#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(24);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r12/f32",
        "southwest" : "r12/f30",
        "south" : "r12/f31",
        "northwest" : "r14/f30",
        "east" : "r13/f32",
        "north" : "r14/f31",
        "northeast" : "r14/f32",
        "west" : "r13/f30",
    ]));
    
}
