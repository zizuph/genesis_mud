#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r05/f16",
        "southwest" : "r05/f14",
        "south" : "r05/f15",
        "northwest" : "r03/f14",
        "east" : "r04/f16",
        "north" : "r03/f15",
        "northeast" : "r03/f16",
        "west" : "r04/f14",
    ]));
    
}
