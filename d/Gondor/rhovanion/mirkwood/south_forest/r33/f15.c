#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r34/f16",
        "southwest" : "r34/f14",
        "south" : "r34/f15",
        "northwest" : "r32/f14",
        "east" : "r33/f16",
        "north" : "r32/f15",
        "northeast" : "r32/f16",
        "west" : "r33/f14",
    ]));
    
}
