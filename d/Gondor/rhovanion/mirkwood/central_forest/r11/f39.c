#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(14);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r10/f40",
        "southwest" : "r10/f38",
        "south" : "r10/f39",
        "northwest" : "r12/f38",
        "east" : "r11/f40",
        "north" : "r12/f39",
        "northeast" : "r12/f40",
        "west" : "r11/f38",
    ]));
    
}
