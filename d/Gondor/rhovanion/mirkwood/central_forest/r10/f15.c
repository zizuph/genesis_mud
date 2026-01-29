#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(17);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r09/f16",
        "southwest" : "r09/f14",
        "south" : "r09/f15",
        "northwest" : "r11/f14",
        "east" : "r10/f16",
        "north" : "r11/f15",
        "northeast" : "r11/f16",
        "west" : "r10/f14",
    ]));
    
}
