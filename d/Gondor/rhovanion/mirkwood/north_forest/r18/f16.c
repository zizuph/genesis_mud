#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r17/f17",
        "southwest" : "r17/f15",
        "south" : "r17/f16",
        "northwest" : "r19/f15",
        "east" : "r18/f17",
        "north" : "r19/f16",
        "northeast" : "r19/f17",
        "west" : "r18/f15",
    ]));
    
}
