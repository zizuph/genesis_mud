#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r36/f16",
        "southwest" : "r36/f14",
        "south" : "r36/f15",
        "northwest" : "r34/f14",
        "east" : "r35/f16",
        "north" : "r34/f15",
        "northeast" : "r34/f16",
        "west" : "r35/f14",
    ]));
    
}
