#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(54);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r05/f16",
        "southwest" : "r05/f14",
        "south" : "r05/f15",
        "northwest" : "r07/f14",
        "east" : "r06/f16",
        "north" : "r07/f15",
        "northeast" : "r07/f16",
        "west" : "r06/f14",
    ]));
    
}
