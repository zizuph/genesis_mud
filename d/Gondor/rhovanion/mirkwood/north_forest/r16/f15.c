#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(12);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r15/f16",
        "southwest" : "r16/f14",
        "south" : "r15/f15",
        "northwest" : "r17/f14",
        "east" : "r16/f16",
        "north" : "r17/f15",
        "northeast" : "r17/f16",
        "west" : "r16/f14",
    ]));
    
}
