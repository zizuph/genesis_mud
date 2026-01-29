#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r10/f15",
        "southwest" : "r10/f13",
        "south" : "r10/f14",
        "northwest" : "r08/f13",
        "east" : "r09/f15",
        "north" : "r08/f14",
        "northeast" : "r08/f15",
        "west" : "r09/f13",
    ]));
    
}
