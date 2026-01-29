#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r17/f17",
        "southwest" : "r17/f15",
        "south" : "r17/f16",
        "northwest" : "r15/f15",
        "east" : "r16/f17",
        "north" : "r15/f16",
        "northeast" : "r15/f17",
        "west" : "r16/f15",
    ]));
    
}
