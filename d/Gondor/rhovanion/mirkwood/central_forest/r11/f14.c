#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(15);

    set_distance_to_edge(6);
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
