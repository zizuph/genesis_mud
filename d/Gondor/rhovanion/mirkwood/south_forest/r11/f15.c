#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r12/f16",
        "southwest" : "r12/f14",
        "south" : "r12/f15",
        "northwest" : "r10/f14",
        "east" : "r11/f16",
        "north" : "r10/f15",
        "northeast" : "r10/f16",
        "west" : "r11/f14",
    ]));
    
}
