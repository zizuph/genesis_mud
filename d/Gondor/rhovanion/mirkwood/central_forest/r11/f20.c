#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(75);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r10/f21",
        "southwest" : "r10/f19",
        "south" : "r10/f20",
        "northwest" : "r12/f19",
        "east" : "r11/f21",
        "north" : "r12/f20",
        "northeast" : "r12/f21",
        "west" : "r11/f19",
    ]));
    
}
