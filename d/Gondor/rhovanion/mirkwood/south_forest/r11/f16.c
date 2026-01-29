#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r12/f17",
        "southwest" : "r12/f15",
        "south" : "r12/f16",
        "northwest" : "r10/f15",
        "east" : "r11/f17",
        "north" : "r10/f16",
        "northeast" : "r10/f17",
        "west" : "r11/f15",
    ]));
    
}
