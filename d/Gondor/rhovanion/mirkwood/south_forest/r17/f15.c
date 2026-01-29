#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r18/f16",
        "southwest" : "r18/f14",
        "south" : "r18/f15",
        "northwest" : "r16/f14",
        "east" : "r17/f16",
        "north" : "r16/f15",
        "northeast" : "r16/f16",
        "west" : "r17/f14",
    ]));
    
}
