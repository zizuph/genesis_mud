#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(12);
    add_mirkwood_exits(([
        "southeast" : "r13/f21",
        "southwest" : "r13/f19",
        "south" : "r13/f20",
        "northwest" : "r11/f19",
        "east" : "r12/f21",
        "north" : "r11/f20",
        "northeast" : "r11/f21",
        "west" : "r12/f19",
    ]));
    
}
