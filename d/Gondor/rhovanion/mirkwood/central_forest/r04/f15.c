#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(22);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r03/f16",
        "southwest" : "r03/f14",
        "south" : "r03/f15",
        "northwest" : "r05/f14",
        "east" : "r04/f16",
        "north" : "r05/f15",
        "northeast" : "r05/f16",
        "west" : "r04/f14",
    ]));
    
}
