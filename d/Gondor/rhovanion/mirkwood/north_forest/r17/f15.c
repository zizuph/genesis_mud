#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(19);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r16/f16",
        "southwest" : "r16/f14",
        "south" : "r16/f15",
        "northwest" : "r18/f14",
        "east" : "r17/f16",
        "north" : "r18/f15",
        "northeast" : "r18/f16",
        "west" : "r17/f14",
    ]));
    
}
