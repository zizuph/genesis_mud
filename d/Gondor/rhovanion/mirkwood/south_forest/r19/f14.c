#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r20/f15",
        "southwest" : "r20/f13",
        "south" : "r20/f14",
        "northwest" : "r18/f13",
        "east" : "r19/f15",
        "north" : "r18/f14",
        "northeast" : "r18/f15",
        "west" : "r19/f13",
    ]));
    
}
