#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(29);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r11/f15",
        "southwest" : "r11/f13",
        "south" : "r11/f14",
        "northwest" : "r13/f13",
        "east" : "r12/f15",
        "north" : "r13/f14",
        "northeast" : "r13/f15",
        "west" : "r12/f13",
    ]));
    
}
