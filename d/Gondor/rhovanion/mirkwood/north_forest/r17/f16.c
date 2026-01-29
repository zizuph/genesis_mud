#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(10);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r16/f17",
        "southwest" : "r16/f15",
        "south" : "r16/f16",
        "northwest" : "r18/f15",
        "east" : "r17/f17",
        "north" : "r18/f16",
        "northeast" : "r18/f17",
        "west" : "r17/f15",
    ]));
    
}
