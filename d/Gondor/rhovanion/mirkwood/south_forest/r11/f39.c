#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(12);

    set_distance_to_edge(11);
    add_mirkwood_exits(([
        "southeast" : "r12/f40",
        "southwest" : "r12/f38",
        "south" : "r12/f39",
        "northwest" : "r10/f38",
        "east" : "r11/f40",
        "north" : "r10/f39",
        "northeast" : "r10/f40",
        "west" : "r11/f38",
    ]));
    
}
