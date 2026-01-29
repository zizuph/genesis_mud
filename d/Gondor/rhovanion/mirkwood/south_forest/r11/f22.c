#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(11);
    add_mirkwood_exits(([
        "southeast" : "r12/f23",
        "southwest" : "r12/f21",
        "south" : "r12/f22",
        "northwest" : "r10/f21",
        "east" : "r11/f23",
        "north" : "r10/f22",
        "northeast" : "r10/f23",
        "west" : "r11/f21",
    ]));
    
}
