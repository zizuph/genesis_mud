#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(15);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r00/f16",
        "southwest" : "r00/f14",
        "south" : "r00/f15",
        "northwest" : "r02/f14",
        "east" : "r01/f16",
        "north" : "r02/f15",
        "northeast" : "r02/f16",
        "west" : "r01/f14",
    ]));
    
}
