#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r18/f17",
        "southwest" : "r18/f15",
        "south" : "r18/f16",
        "northwest" : "r16/f15",
        "east" : "r17/f17",
        "north" : "r16/f16",
        "northeast" : "r16/f17",
        "west" : "r17/f15",
    ]));
    
}
