#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(19);

    set_distance_to_edge(10);
    add_mirkwood_exits(([
        "southeast" : "r12/f41",
        "southwest" : "r12/f39",
        "south" : "r12/f40",
        "northwest" : "r10/f39",
        "east" : "r11/f41",
        "north" : "r10/f40",
        "northeast" : "r10/f41",
        "west" : "r11/f39",
    ]));
    
}
