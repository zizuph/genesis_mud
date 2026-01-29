#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r35/f15",
        "southwest" : "r35/f13",
        "south" : "r35/f14",
        "northwest" : "r33/f13",
        "east" : "r34/f15",
        "north" : "r33/f14",
        "northeast" : "r33/f15",
        "west" : "r34/f13",
    ]));
    
}
