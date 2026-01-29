#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r17/f33",
        "southwest" : "r17/f31",
        "south" : "r17/f32",
        "northwest" : "r15/f31",
        "east" : "r16/f33",
        "north" : "r15/f32",
        "northeast" : "r15/f33",
        "west" : "r16/f31",
    ]));
    
}
