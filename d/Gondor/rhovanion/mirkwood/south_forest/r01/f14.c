#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r02/f15",
        "southwest" : "r02/f13",
        "south" : "r02/f14",
        "northwest" : "r00/f13",
        "east" : "r01/f15",
        "north" : "r00/f14",
        "northeast" : "r00/f15",
        "west" : "r01/f13",
    ]));
    
}
