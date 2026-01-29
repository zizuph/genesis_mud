#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r19/f33",
        "southwest" : "r19/f31",
        "south" : "r19/f32",
        "northwest" : "r17/f31",
        "east" : "r18/f33",
        "north" : "r17/f32",
        "northeast" : "r17/f33",
        "west" : "r18/f31",
    ]));
    
}
