#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(12);
    add_mirkwood_exits(([
        "southeast" : "r13/f22",
        "southwest" : "r13/f20",
        "south" : "r13/f21",
        "northwest" : "r11/f20",
        "east" : "r12/f22",
        "north" : "r11/f21",
        "northeast" : "r11/f22",
        "west" : "r12/f20",
    ]));
    
}
