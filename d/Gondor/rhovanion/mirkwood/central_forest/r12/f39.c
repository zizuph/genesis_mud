#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(16);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r11/f40",
        "southwest" : "r11/f38",
        "south" : "r11/f39",
        "northwest" : "r13/f38",
        "east" : "r12/f40",
        "north" : "r13/f39",
        "northeast" : "r13/f40",
        "west" : "r12/f38",
    ]));
    
}
