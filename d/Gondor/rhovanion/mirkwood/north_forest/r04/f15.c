#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(4);
    set_spider_nest_chance(42);

    set_distance_to_edge(3);
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
