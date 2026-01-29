#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(10);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r09/f15",
        "southwest" : "r09/f13",
        "south" : "r09/f14",
        "northwest" : "r11/f13",
        "east" : "r10/f15",
        "north" : "r11/f14",
        "northeast" : "r11/f15",
        "west" : "r10/f13",
    ]));
    
}
