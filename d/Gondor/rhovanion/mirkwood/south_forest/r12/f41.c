#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r13/f42",
        "southwest" : "r13/f40",
        "south" : "r13/f41",
        "northwest" : "r11/f40",
        "east" : "r12/f42",
        "north" : "r11/f41",
        "northeast" : "r11/f42",
        "west" : "r12/f40",
    ]));
    
}
