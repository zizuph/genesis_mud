#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r19/f16",
        "southwest" : "r19/f14",
        "south" : "r19/f15",
        "northwest" : "r17/f14",
        "east" : "r18/f16",
        "north" : "r17/f15",
        "northeast" : "r17/f16",
        "west" : "r18/f14",
    ]));
    
}
