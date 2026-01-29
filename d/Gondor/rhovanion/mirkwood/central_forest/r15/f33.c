#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(25);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r14/f34",
        "southwest" : "r14/f32",
        "south" : "r14/f33",
        "northwest" : "r16/f32",
        "east" : "r15/f34",
        "north" : "r16/f33",
        "northeast" : "r16/f34",
        "west" : "r15/f32",
    ]));
    
}
