#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r38/f16",
        "southwest" : "r38/f14",
        "south" : "r38/f15",
        "northwest" : "r36/f14",
        "east" : "r37/f16",
        "north" : "r36/f15",
        "northeast" : "r36/f16",
        "west" : "r37/f14",
    ]));
    
}
