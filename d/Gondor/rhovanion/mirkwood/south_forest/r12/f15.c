#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r13/f16",
        "southwest" : "r13/f14",
        "south" : "r13/f15",
        "northwest" : "r11/f14",
        "east" : "r12/f16",
        "north" : "r11/f15",
        "northeast" : "r11/f16",
        "west" : "r12/f14",
    ]));
    
}
