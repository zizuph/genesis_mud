#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r16/f15",
        "southwest" : "r17/f13",
        "south" : "r16/f14",
        "northwest" : "r18/f13",
        "east" : "r17/f15",
        "north" : "r18/f14",
        "northeast" : "r18/f15",
        "west" : "r17/f13",
    ]));
    
}
