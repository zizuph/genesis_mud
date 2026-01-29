#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r17/f15",
        "southwest" : "r17/f13",
        "south" : "r17/f14",
        "northwest" : "r15/f13",
        "east" : "r16/f15",
        "north" : "r15/f14",
        "northeast" : "r15/f15",
        "west" : "r16/f13",
    ]));
    
}
