#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(56);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r09/f21",
        "southwest" : "r09/f19",
        "south" : "r09/f20",
        "northwest" : "r11/f19",
        "east" : "r10/f21",
        "north" : "r11/f20",
        "northeast" : "r11/f21",
        "west" : "r10/f19",
    ]));
    
}
