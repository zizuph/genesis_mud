#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(10);
    add_mirkwood_exits(([
        "southeast" : "r13/f17",
        "southwest" : "r13/f15",
        "south" : "r13/f16",
        "northwest" : "r11/f15",
        "east" : "r12/f17",
        "north" : "r11/f16",
        "northeast" : "r11/f17",
        "west" : "r12/f15",
    ]));
    
}
