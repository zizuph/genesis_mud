#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(25);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r08/f16",
        "southwest" : "r08/f14",
        "south" : "r08/f15",
        "northwest" : "r10/f14",
        "east" : "r09/f16",
        "north" : "r10/f15",
        "northeast" : "r10/f16",
        "west" : "r09/f14",
    ]));
    
}
