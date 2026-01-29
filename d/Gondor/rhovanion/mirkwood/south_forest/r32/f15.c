#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r33/f16",
        "southwest" : "r33/f14",
        "south" : "r33/f15",
        "northwest" : "r31/f14",
        "east" : "r32/f16",
        "north" : "r31/f15",
        "northeast" : "r31/f16",
        "west" : "r32/f14",
    ]));
    
}
