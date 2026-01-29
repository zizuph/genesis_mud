#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(16);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r03/f15",
        "southwest" : "r03/f13",
        "south" : "r03/f14",
        "northwest" : "r05/f13",
        "east" : "r04/f15",
        "north" : "r05/f14",
        "northeast" : "r05/f15",
        "west" : "r04/f13",
    ]));
    
}
