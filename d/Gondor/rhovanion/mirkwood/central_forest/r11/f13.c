#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(14);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r10/f14",
        "southwest" : "r10/f12",
        "south" : "r10/f13",
        "northwest" : "r12/f12",
        "east" : "r11/f14",
        "north" : "r12/f13",
        "northeast" : "r12/f14",
        "west" : "r11/f12",
    ]));
    
}
