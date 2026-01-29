#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r18/f15",
        "southwest" : "r18/f13",
        "south" : "r18/f14",
        "northwest" : "r16/f13",
        "east" : "r17/f15",
        "north" : "r16/f14",
        "northeast" : "r16/f15",
        "west" : "r17/f13",
    ]));
    
}
