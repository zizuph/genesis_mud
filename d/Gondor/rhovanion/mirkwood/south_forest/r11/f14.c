#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r12/f15",
        "southwest" : "r12/f13",
        "south" : "r12/f14",
        "northwest" : "r10/f13",
        "east" : "r11/f15",
        "north" : "r10/f14",
        "northeast" : "r10/f15",
        "west" : "r11/f13",
    ]));
    
}
