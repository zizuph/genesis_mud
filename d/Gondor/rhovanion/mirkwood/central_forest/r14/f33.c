#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(20);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r13/f34",
        "southwest" : "r13/f32",
        "south" : "r13/f33",
        "northwest" : "r15/f32",
        "east" : "r14/f34",
        "north" : "r15/f33",
        "northeast" : "r15/f34",
        "west" : "r14/f32",
    ]));
    
}
