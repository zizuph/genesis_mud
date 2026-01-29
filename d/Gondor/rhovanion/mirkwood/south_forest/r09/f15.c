#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r10/f16",
        "southwest" : "r10/f14",
        "south" : "r10/f15",
        "northwest" : "r08/f14",
        "east" : "r09/f16",
        "north" : "r08/f15",
        "northeast" : "r08/f16",
        "west" : "r09/f14",
    ]));
    
}
