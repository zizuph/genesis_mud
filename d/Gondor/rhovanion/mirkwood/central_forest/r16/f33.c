#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(26);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r15/f34",
        "southwest" : "r15/f32",
        "south" : "r15/f33",
        "northwest" : "r17/f32",
        "east" : "r16/f34",
        "north" : "r17/f33",
        "northeast" : "r17/f34",
        "west" : "r16/f32",
    ]));
    
}
