#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r02/f16",
        "southwest" : "r02/f14",
        "south" : "r02/f15",
        "northwest" : "r00/f14",
        "east" : "r01/f16",
        "north" : "r00/f15",
        "northeast" : "r00/f16",
        "west" : "r01/f14",
    ]));
    
}
