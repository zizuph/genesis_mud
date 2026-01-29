#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(19);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r08/f15",
        "southwest" : "r08/f13",
        "south" : "r08/f14",
        "northwest" : "r10/f13",
        "east" : "r09/f15",
        "north" : "r10/f14",
        "northeast" : "r10/f15",
        "west" : "r09/f13",
    ]));
    
}
