#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(71);

    set_distance_to_edge(8);
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
