#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r06/f16",
        "southwest" : "r06/f14",
        "south" : "r06/f15",
        "northwest" : "r04/f14",
        "east" : "r05/f16",
        "north" : "r04/f15",
        "northeast" : "r04/f16",
        "west" : "r05/f14",
    ]));
    
}
