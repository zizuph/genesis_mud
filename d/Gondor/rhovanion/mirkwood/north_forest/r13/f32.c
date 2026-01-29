#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
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
