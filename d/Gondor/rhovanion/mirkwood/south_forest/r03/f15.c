#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r04/f16",
        "southwest" : "r04/f14",
        "south" : "r04/f15",
        "northwest" : "r02/f14",
        "east" : "r03/f16",
        "north" : "r02/f15",
        "northeast" : "r02/f16",
        "west" : "r03/f14",
    ]));
    
}
