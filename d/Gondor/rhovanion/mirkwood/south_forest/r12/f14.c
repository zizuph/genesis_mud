#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r13/f15",
        "southwest" : "r13/f13",
        "south" : "r13/f14",
        "northwest" : "r11/f13",
        "east" : "r12/f15",
        "north" : "r11/f14",
        "northeast" : "r11/f15",
        "west" : "r12/f13",
    ]));
    
}
