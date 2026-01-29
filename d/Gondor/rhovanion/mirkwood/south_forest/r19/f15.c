#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r20/f16",
        "southwest" : "r20/f14",
        "south" : "r20/f15",
        "northwest" : "r18/f14",
        "east" : "r19/f16",
        "north" : "r18/f15",
        "northeast" : "r18/f16",
        "west" : "r19/f14",
    ]));
    
}
