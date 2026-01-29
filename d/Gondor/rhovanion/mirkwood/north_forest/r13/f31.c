#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
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
