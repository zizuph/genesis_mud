#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(11);
    add_mirkwood_exits(([
        "southeast" : "r12/f22",
        "southwest" : "r12/f20",
        "south" : "r12/f21",
        "northwest" : "r10/f20",
        "east" : "r11/f22",
        "north" : "r10/f21",
        "northeast" : "r10/f22",
        "west" : "r11/f20",
    ]));
    
}
