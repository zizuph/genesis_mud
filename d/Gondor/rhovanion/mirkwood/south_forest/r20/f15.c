#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r20/f16",
        "southwest" : "r20/f14",
        "south" : "r20/f15",
        "northwest" : "r19/f14",
        "east" : "r20/f16",
        "north" : "r19/f15",
        "northeast" : "r19/f16",
        "west" : "r20/f14",
    ]));
    
}
