#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r19/f15",
        "southwest" : "r19/f13",
        "south" : "r19/f14",
        "northwest" : "r17/f13",
        "east" : "r18/f15",
        "north" : "r17/f14",
        "northeast" : "r17/f15",
        "west" : "r18/f13",
    ]));
    
}
