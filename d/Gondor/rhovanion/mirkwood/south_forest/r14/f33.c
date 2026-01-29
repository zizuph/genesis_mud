#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r15/f34",
        "southwest" : "r15/f32",
        "south" : "r15/f33",
        "northwest" : "r13/f32",
        "east" : "r14/f34",
        "north" : "r13/f33",
        "northeast" : "r13/f34",
        "west" : "r14/f32",
    ]));
    
}
