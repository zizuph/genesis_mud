#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(12);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r10/f41",
        "southwest" : "r10/f39",
        "south" : "r10/f40",
        "northwest" : "r12/f39",
        "east" : "r11/f41",
        "north" : "r12/f40",
        "northeast" : "r12/f41",
        "west" : "r11/f39",
    ]));
    
}
