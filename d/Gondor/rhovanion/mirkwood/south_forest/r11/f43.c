#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r12/f44",
        "southwest" : "r12/f42",
        "south" : "r12/f43",
        "northwest" : "r10/f42",
        "east" : "r11/f44",
        "north" : "r10/f43",
        "northeast" : "r10/f44",
        "west" : "r11/f42",
    ]));
    
}
