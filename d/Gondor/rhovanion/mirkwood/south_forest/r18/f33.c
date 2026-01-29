#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r19/f34",
        "southwest" : "r19/f32",
        "south" : "r19/f33",
        "northwest" : "r17/f32",
        "east" : "r18/f34",
        "north" : "r17/f33",
        "northeast" : "r17/f34",
        "west" : "r18/f32",
    ]));
    
}
