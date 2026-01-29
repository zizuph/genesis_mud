#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(19);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r12/f42",
        "southwest" : "r12/f40",
        "south" : "r12/f41",
        "northwest" : "r10/f40",
        "east" : "r11/f42",
        "north" : "r10/f41",
        "northeast" : "r10/f42",
        "west" : "r11/f40",
    ]));
    
}
