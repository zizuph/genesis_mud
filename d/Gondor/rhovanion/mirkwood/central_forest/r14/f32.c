#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(29);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r13/f33",
        "southwest" : "r13/f31",
        "south" : "r13/f32",
        "northwest" : "r15/f31",
        "east" : "r14/f33",
        "north" : "r15/f32",
        "northeast" : "r15/f33",
        "west" : "r14/f31",
    ]));
    
}
