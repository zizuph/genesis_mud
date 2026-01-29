#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(19);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r01/f16",
        "southwest" : "r01/f14",
        "south" : "r01/f15",
        "northwest" : "r03/f14",
        "east" : "r02/f16",
        "north" : "r03/f15",
        "northeast" : "r03/f16",
        "west" : "r02/f14",
    ]));
    
}
