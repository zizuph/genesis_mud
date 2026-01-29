#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(14);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r15/f17",
        "southwest" : "r15/f15",
        "south" : "r15/f16",
        "northwest" : "r17/f15",
        "east" : "r16/f17",
        "north" : "r17/f16",
        "northeast" : "r17/f17",
        "west" : "r16/f15",
    ]));
    
}
