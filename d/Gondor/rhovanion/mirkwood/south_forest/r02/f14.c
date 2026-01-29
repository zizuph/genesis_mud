#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r03/f15",
        "southwest" : "r03/f13",
        "south" : "r03/f14",
        "northwest" : "r01/f13",
        "east" : "r02/f15",
        "north" : "r01/f14",
        "northeast" : "r01/f15",
        "west" : "r02/f13",
    ]));
    
}
