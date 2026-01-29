#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r13/f43",
        "southwest" : "r13/f41",
        "south" : "r13/f42",
        "northwest" : "r11/f41",
        "east" : "r12/f43",
        "north" : "r11/f42",
        "northeast" : "r11/f43",
        "west" : "r12/f41",
    ]));
    
}
