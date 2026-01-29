#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(55);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r10/f17",
        "southwest" : "r10/f15",
        "south" : "r10/f16",
        "northwest" : "r12/f15",
        "east" : "r11/f17",
        "north" : "r12/f16",
        "northeast" : "r12/f17",
        "west" : "r11/f15",
    ]));
    
}
