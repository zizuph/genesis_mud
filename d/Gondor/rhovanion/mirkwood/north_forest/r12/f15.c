#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(4);
    set_spider_nest_chance(49);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r11/f16",
        "southwest" : "r11/f14",
        "south" : "r11/f15",
        "northwest" : "r13/f14",
        "east" : "r12/f16",
        "north" : "r13/f15",
        "northeast" : "r13/f16",
        "west" : "r12/f14",
    ]));
    
}
