#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r34/f15",
        "southwest" : "r34/f13",
        "south" : "r34/f14",
        "northwest" : "r32/f13",
        "east" : "r33/f15",
        "north" : "r32/f14",
        "northeast" : "r32/f15",
        "west" : "r33/f13",
    ]));
    
}
