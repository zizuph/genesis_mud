#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(63);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r10/f15",
        "southwest" : "r10/f13",
        "south" : "r10/f14",
        "northwest" : "r12/f13",
        "east" : "r11/f15",
        "north" : "r12/f14",
        "northeast" : "r12/f15",
        "west" : "r11/f13",
    ]));
    
}
