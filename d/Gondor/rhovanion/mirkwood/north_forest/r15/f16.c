#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(29);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r14/f17",
        "southwest" : "r15/f15",
        "south" : "r14/f16",
        "northwest" : "r16/f15",
        "east" : "r15/f17",
        "north" : "r16/f16",
        "northeast" : "r16/f17",
        "west" : "r15/f15",
    ]));
    
}
