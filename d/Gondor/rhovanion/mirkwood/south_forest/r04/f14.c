#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r05/f15",
        "southwest" : "r05/f13",
        "south" : "r05/f14",
        "northwest" : "r03/f13",
        "east" : "r04/f15",
        "north" : "r03/f14",
        "northeast" : "r03/f15",
        "west" : "r04/f13",
    ]));
    
}
